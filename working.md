# How the Project Works

This document explains the technical working of the ESP32 Wi-Fi Beacon Frame Research program.

---

# 1. Program Initialization

The program starts with:

```cpp
void setup()
```

The initialization process is:

```text
ESP32 Starts
     ↓
Serial Initialization
     ↓
Random Initialization
     ↓
Wi-Fi Initialization
     ↓
Channel Configuration
     ↓
Ready
```

---

## Serial Initialization

```cpp
Serial.begin(115200);
```

Starts serial communication between the ESP32 and the computer.

The communication speed is:

```text
115200 baud
```

---

## Random Initialization

```cpp
randomSeed(esp_random());
```

Uses the ESP32 random-number generator to initialize random values.

These random values are later used by the program when generating experimental SSID variants and BSSID values.

---

## Base Name

```cpp
const char *baseName = "student-wifi";
```

Defines the base SSID used by the program.

---

# 2. Wi-Fi Configuration

The program configures the ESP32 Wi-Fi interface.

---

## Station Mode

```cpp
WiFi.mode(WIFI_STA);
```

Sets the ESP32 Wi-Fi interface to station mode.

```text
ESP32
  ↓
WIFI_STA
  ↓
Station Mode
```

---

## Disconnect

```cpp
WiFi.disconnect();
```

Disconnects the ESP32 from an existing Wi-Fi connection.

---

## Promiscuous Mode

```cpp
esp_wifi_set_promiscuous(true);
```

Enables the ESP32 Wi-Fi driver's promiscuous functionality for the low-level wireless experiment.

---

## Channel Selection

```cpp
esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
```

Configures the Wi-Fi interface for channel 1.

```text
Primary Channel → 1
Secondary Channel → None
```

---

# 3. Beacon Packet Buffer

The program creates a buffer:

```cpp
uint8_t beaconPacket[128];
```

This buffer stores the bytes that make up the constructed Wi-Fi frame.

Conceptually:

```text
beaconPacket[]
       │
       ├── Frame Header
       ├── Address Fields
       ├── Beacon Information
       ├── SSID
       ├── Supported Rates
       └── Channel Information
```

---

# 4. Frame Header

The first bytes are initialized:

```cpp
beaconPacket[0] = 0x80;
beaconPacket[1] = 0x00;
beaconPacket[2] = 0x00;
beaconPacket[3] = 0x00;
```

The frame-control value identifies the constructed frame as a beacon management frame.

---

# 5. Destination Address

The destination address is filled with:

```cpp
0xff
```

using:

```cpp
for (int i = 4; i <= 9; i++)
    beaconPacket[i] = 0xff;
```

This produces:

```text
FF:FF:FF:FF:FF:FF
```

which is the broadcast MAC address.

---

# 6. SSID Characters

The program defines four Unicode characters:

```cpp
const char *invisible[4] = {
    "\xE2\x80\x8B",
    "\xE2\x80\x8C",
    "\xE2\x80\x8D",
    "\xE2\x81\xA0"
};
```

These are zero-width or visually invisible Unicode characters.

They are stored as UTF-8 byte sequences.

---

# 7. SSID Generation

The program generates a random value:

```cpp
uint32_t idx = esp_random();
```

The value is used to select Unicode characters.

The base name is first copied:

```cpp
memcpy(ssid, baseName, baseLen);
```

Then Unicode characters are appended.

```text
student-wifi
      +
Unicode characters
      ↓
Generated SSID byte sequence
```

The important concept is:

```text
Visually similar
      ≠
Same underlying bytes
```

---

# 8. Number of SSID Variations

The program uses:

```cpp
const uint8_t DIGITS = 6;
```

There are four possible Unicode characters for each position.

Therefore:

```text
4⁶ = 4096
```

possible combinations.

---

# 9. SSID Information Element

The generated SSID is inserted into the packet:

```cpp
beaconPacket[36] = 0x00;
beaconPacket[37] = len;
memcpy(&beaconPacket[38], ssid, len);
```

The structure is:

```text
┌──────────────┐
│ Element ID   │
├──────────────┤
│ Length       │
├──────────────┤
│ SSID Data    │
└──────────────┘
```

The SSID element ID is:

```text
0x00
```

---

# 10. Supported Rates

The program adds supported-rate information:

```cpp
beaconPacket[p++] = 0x01;
beaconPacket[p++] = 0x08;
```

This is followed by the rate values.

```text
Supported Rates
      │
      ├── Rate 1
      ├── Rate 2
      ├── Rate 3
      ├── Rate 4
      ├── Rate 5
      ├── Rate 6
      ├── Rate 7
      └── Rate 8
```

---

# 11. Channel Information

The program adds channel information:

```cpp
beaconPacket[p++] = 0x03;
beaconPacket[p++] = 0x01;
beaconPacket[p++] = 1;
```

Conceptually:

```text
Element ID
     ↓
Length
     ↓
Channel Number
```

The configured channel is:

```text
Channel 1
```

---

# 12. BSSID Generation

The program generates six random bytes:

```cpp
for (int j = 10; j <= 15; j++)
    beaconPacket[j] = random(256);
```

Each byte has a possible value from:

```text
0 – 255
```

The six bytes form a MAC-address-style value:

```text
XX:XX:XX:XX:XX:XX
```

The related address bytes are copied using:

```cpp
for (int j = 16; j <= 21; j++)
    beaconPacket[j] = beaconPacket[j - 6];
```

---

# 13. Packet Position

The variable:

```cpp
int p
```

keeps track of the current position in the packet.

When information is added:

```cpp
p++;
```

moves the position forward.

At the end, `p` represents the constructed packet length.

---

# 14. Packet Construction

The complete packet construction process is:

```text
Create packet buffer
        ↓
Set frame header
        ↓
Set destination
        ↓
Set address fields
        ↓
Generate SSID
        ↓
Add SSID information
        ↓
Add supported rates
        ↓
Add channel information
        ↓
Packet ready
```

---

# 15. Repetition

The program defines:

```cpp
const uint8_t REPEATS = 10;
```

The loop:

```cpp
for (int i = 0; i < REPEATS; i++)
```

controls repeated processing of the constructed test frame.

---

# 16. Low-Level Transmission

The constructed packet is passed to the ESP32 Wi-Fi driver:

```cpp
esp_wifi_80211_tx(
    WIFI_IF_STA,
    beaconPacket,
    p,
    false
);
```

The parameters represent:

| Parameter | Purpose |
|---|---|
| `WIFI_IF_STA` | Station interface |
| `beaconPacket` | Packet buffer |
| `p` | Packet length |
| `false` | Transmission parameter |

This provides low-level access to the ESP32 Wi-Fi transmission mechanism.

---

# 17. Complete Program Flow

```text
             ESP32 START
                  │
                  ▼
               setup()
                  │
                  ▼
          Initialize Serial
                  │
                  ▼
          Initialize Random
                  │
                  ▼
           Configure Wi-Fi
                  │
                  ▼
           Select Channel
                  │
                  ▼
               loop()
                  │
                  ▼
        Generate SSID Variant
                  │
                  ▼
        Build Beacon Packet
                  │
                  ▼
         Generate BSSID
                  │
                  ▼
         Transmit Frame
                  │
                  ▼
              Repeat
                  │
                  └──────────► loop()
```

---

# 18. Important Variables

| Variable | Purpose |
|---|---|
| `beaconPacket` | Stores the Wi-Fi frame |
| `baseName` | Base SSID |
| `baseLen` | Base SSID length |
| `invisible[]` | Unicode characters |
| `DIGITS` | Unicode positions |
| `REPEATS` | Repetition count |
| `idx` | Random selector |
| `ssid[]` | Generated SSID |
| `sufLen` | Suffix length |
| `len` | Total SSID length |
| `p` | Packet position/length |

---

# 19. Technical Concepts

## IEEE 802.11

A family of standards used for Wi-Fi wireless communication.

## Beacon Frame

A Wi-Fi management frame used to advertise wireless-network information.

## SSID

**Service Set Identifier**

The Wi-Fi network name normally displayed to users.

Example:

```text
student-wifi
```

## BSSID

**Basic Service Set Identifier**

An identifier associated with a wireless basic service set and commonly represented using a MAC address.

Example:

```text
AA:BB:CC:DD:EE:FF
```

## MAC Address

A six-byte network interface identifier normally written in hexadecimal.

Example:

```text
24:6F:28:AA:BB:CC
```

## Unicode

A standard for representing characters and symbols.

## UTF-8

An encoding format used to represent Unicode characters as bytes.

## ESP32

A microcontroller family with built-in Wi-Fi and Bluetooth capabilities.

---

# 20. Learning Outcome

By studying this program, you can understand:

- ESP32 Wi-Fi initialization
- Wi-Fi channel configuration
- Beacon-frame structure
- SSID construction
- BSSID and MAC addresses
- Unicode and UTF-8
- Packet construction
- Low-level ESP32 Wi-Fi functions
- Basic wireless-security concepts

---

## ⚠️ Responsible Research

This code should only be used in an **authorized and controlled environment**.

Use only equipment and networks that you own or have explicit permission to test.

The purpose of this project is to learn about **ESP32, Wi-Fi protocols, IEEE 802.11 management frames, and wireless-security concepts**.
