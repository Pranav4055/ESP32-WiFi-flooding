# ESP32 Wi-Fi Beacon Frame Research

> **Educational Cybersecurity & Embedded Systems Project**

An ESP32-based research project for studying the structure and transmission of IEEE 802.11 Wi-Fi beacon frames.

The project demonstrates how an ESP32 can construct a custom beacon frame, modify SSID information, generate test BSSID values, and transmit 802.11 management frames for controlled wireless-security experimentation.

---

## ⚠️ Responsible Use & Disclaimer

**This project is strictly for educational, research, and authorized security-testing purposes.**

- Use the project **only in an isolated or controlled test environment**.
- Test only on networks, devices, and wireless equipment that **you own or have explicit permission to test**.
- Do not use this project to interfere with public, college, office, home, or other third-party Wi-Fi networks.
- Do not attempt to disrupt, overload, impersonate, or interfere with networks belonging to other people.
- Follow the wireless regulations applicable in your country.
- The author is not responsible for misuse of this project.

**Recommended setup:** use a controlled laboratory environment and, where appropriate, RF isolation/shielding.

---

# 📌 Project Overview

Wi-Fi networks periodically transmit **beacon frames** to advertise information about a wireless network.

This project uses an ESP32 to demonstrate the construction of such frames at the 802.11 management-frame level.

### Main concepts demonstrated

- ESP32 Wi-Fi functionality
- IEEE 802.11 beacon frames
- SSID information elements
- BSSID/MAC-address fields
- Supported-rate information
- Wi-Fi channel configuration
- Raw 802.11 frame transmission
- Unicode/zero-width characters
- Embedded systems programming
- Wireless-security research

---

# 🧠 How It Works

The basic operation of the project can be represented as:

```text
                    ┌─────────────────────┐
                    │       ESP32         │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │ Initialize Wi-Fi    │
                    │ Hardware            │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │ Configure Test      │
                    │ Channel              │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │ Generate SSID       │
                    │ Variant             │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │ Construct 802.11    │
                    │ Beacon Frame        │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │ Generate Test       │
                    │ BSSID               │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │ Transmit for        │
                    │ Controlled Research │
                    └─────────────────────┘
```

---

# 🔍 Important Parts of the Program

### 1. ESP32 Wi-Fi libraries

The project uses the ESP32 Wi-Fi functionality provided by the Arduino ESP32 core.

```cpp
#include <WiFi.h>
#include "esp_wifi.h"
```

`WiFi.h` provides the normal ESP32 Wi-Fi functionality, while `esp_wifi.h` provides access to lower-level ESP32 Wi-Fi functionality.

---

### 2. Base SSID

The project starts with a configurable base name:

```cpp
const char *baseName = "student-wifi";
```

You can change this value for your own controlled experiment.

---

### 3. Invisible Unicode characters

The program defines several Unicode characters that do not normally appear visibly when displayed.

These are used to create different byte sequences while keeping the visible SSID appearance similar.

This demonstrates an important cybersecurity concept:

> **Two strings can look identical to a human while containing different underlying bytes.**

---

### 4. Beacon frame

The program manually constructs fields of an IEEE 802.11 beacon frame.

Conceptually:

```text
802.11 Header
     │
     ├── Destination
     ├── Source / BSSID
     ├── Frame Control
     │
     ▼
SSID Information Element
     │
     ▼
Supported Rates
     │
     ▼
Channel Information
```

---

### 5. Random BSSID values

The experiment generates different BSSID values for its test frames.

This is useful for understanding why wireless scanners may display multiple apparently different access points during controlled testing.

---

# 🛠️ Requirements

## Hardware

- ESP32 development board
- USB data cable
- Computer
- Optional isolated wireless test environment

## Software

- Arduino IDE
- ESP32 board support package
- USB drivers if required by your particular ESP32 board

Arduino IDE supports Windows and macOS. citeturn0search1turn0search5

---

# 💻 1. Install Arduino IDE

## Windows

Download Arduino IDE from the official Arduino website:

[Arduino IDE — Official Download](https://www.arduino.cc/en/software?utm_source=chatgpt.com)

After downloading:

1. Run the `.exe` installer.
2. Follow the installation instructions.
3. Open **Arduino IDE**.

Arduino's current IDE documentation lists Windows 10 64-bit and newer as supported for Arduino IDE 2. citeturn0search1

---

# 🍎 2. Install Arduino IDE on macOS

Download Arduino IDE:

[Arduino IDE — Official Download](https://www.arduino.cc/en/software?utm_source=chatgpt.com)

Steps:

1. Download the macOS version.
2. Open the `.dmg` file.
3. Drag **Arduino IDE** into the `Applications` folder.
4. Open Arduino IDE.

Arduino provides builds for both Intel and Apple Silicon Macs. citeturn0search1turn0search3

---

# 🔧 3. Install ESP32 Board Support

After installing Arduino IDE, ESP32 support must be added.

Espressif recommends installing the Arduino-ESP32 core through **Boards Manager**. citeturn0search0turn0search2

### Step 1 — Open Preferences

In Arduino IDE:

```text
File
   ↓
Preferences
```

On macOS:

```text
Arduino IDE
   ↓
Settings / Preferences
```

Find:

```text
Additional Boards Manager URLs
```

Add the official ESP32 package URL:

```text
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

Then click **OK**.

---

# 📦 4. Install ESP32 from Board Manager

Go to:

```text
Tools
   ↓
Board
      ↓
Boards Manager
```

Search:

```text
ESP32
```

Install:

```text
esp32 by Espressif Systems
```

After installation, restart Arduino IDE if necessary.

The official Espressif documentation recommends the Boards Manager method for installing Arduino-ESP32. citeturn0search0

---

# 📝 5. Create a New Sketch

Open Arduino IDE.

Select:

```text
File
   ↓
New Sketch
```

A new Arduino sketch will appear.

You can then copy the project source code into the sketch.

For this repository, the source should eventually be saved as:

```text
src/beacon_research.ino
```

---

# 🧩 6. Select Your ESP32 Board

Connect your ESP32 to your computer using a **USB data cable**.

Then go to:

```text
Tools
   ↓
Board
   ↓
ESP32 Arduino
```

Select the **exact board model you own**.

For example, depending on your hardware:

```text
ESP32 Dev Module
ESP32 DevKitC
ESP32-S3 Dev Module
ESP32-C3 Dev Module
```

Do **not** blindly select a different ESP32 model.

The correct board selection matters because different ESP32 variants have different hardware configurations. Espressif also provides a generic `ESP32-XX Dev Module` option when an exact board is not listed. citeturn0search7

---

# 🔌 7. Select the ESP32 Port

With the ESP32 connected, go to:

```text
Tools
   ↓
Port
```

Select the port belonging to your ESP32.

### macOS

It may look similar to:

```text
/dev/cu.usbserial-XXXX
```

or

```text
/dev/cu.SLAB_USBtoUART
```

### Windows

It normally appears as something similar to:

```text
COM3
COM4
COM5
```

The exact name depends on the USB-to-serial chip and operating system.

If multiple ports are shown, disconnect the ESP32, check the list, reconnect it, and select the newly appearing port.

---

# ⚙️ 8. Upload the Program

Before uploading, check:

```text
Tools → Board
```

and

```text
Tools → Port
```

Then click:

```text
Upload
```

Arduino IDE will:

```text
Compile
    ↓
Build
    ↓
Connect to ESP32
    ↓
Flash program
    ↓
Restart ESP32
```

Some ESP32 boards may require pressing the **BOOT** button during upload if the board does not automatically enter download mode.

---

# 🖥️ 9. Open Serial Monitor

After uploading:

```text
Tools
   ↓
Serial Monitor
```

Set the baud rate to:

```text
115200
```

The program uses:

```cpp
Serial.begin(115200);
```

Therefore the Serial Monitor must use the same speed.

You should then see the project's startup/debug information.

---

# ⚙️ Configuration

The main experiment parameters are defined near the beginning of the source code.

| Parameter | Purpose |
|---|---|
| `baseName` | Base SSID used by the experiment |
| `DIGITS` | Number of invisible-character positions |
| `REPEATS` | Number of frame transmissions per generated variant |
| `invisible[]` | Unicode characters used for the experiment |
| Wi-Fi channel | Test channel selected by the program |

For safe experimentation, keep testing within your controlled wireless environment.

---

# 📁 Project Structure

```text
ESP32-WiFi-Beacon-Research/
│
├── README.md
│
├── src/
│   └── beacon_research.ino
│
├── docs/
│   └── working.md
│
├── images/
│   └── architecture.png
│
└── LICENSE
```

---

# 🧪 Suggested Laboratory Setup

For responsible testing:

```text
                 CONTROLLED LAB
        ┌────────────────────────────┐
        │                            │
        │       ESP32 Test Device    │
        │              │             │
        │              ▼             │
        │      Wi-Fi Test Equipment  │
        │                            │
        │      Isolated Environment  │
        │                            │
        └────────────────────────────┘
```

Avoid testing in crowded public Wi-Fi environments such as:

- College campuses
- Airports
- Cafes
- Hotels
- Offices
- Public hotspots

Use equipment and networks that you own or have explicit authorization to test.

---

# 🐛 Troubleshooting

### ESP32 board does not appear

Try:

- Check the USB cable.
- Make sure it is a **data cable**, not charge-only.
- Try another USB port.
- Install the appropriate USB-to-serial driver if your board requires one.
- Restart Arduino IDE.

---

### Port does not appear

Disconnect the ESP32 and reconnect it.

Then check:

```text
Tools → Port
```

On macOS, look for a new `/dev/cu.*` device.

On Windows, look for a new `COM*` port.

---

### Upload fails

Check:

1. Correct ESP32 board selected.
2. Correct port selected.
3. USB cable connected properly.
4. Try pressing the ESP32 **BOOT** button during upload.
5. Try a lower upload speed if your particular board/cable is unreliable.

---

### Serial Monitor shows garbage

Make sure the Serial Monitor is configured for:

```text
115200 baud
```

because the program starts Serial communication with:

```cpp
Serial.begin(115200);
```

---

# 🎓 Learning Objectives

After studying this project, you should understand:

- How ESP32 Wi-Fi hardware is initialized.
- What an IEEE 802.11 beacon frame is.
- How SSID information is represented inside a frame.
- What a BSSID represents.
- How Wi-Fi management frames are structured.
- How Unicode characters are represented as bytes.
- How embedded C/C++ is used for wireless experimentation.
- Why unauthorized wireless-frame transmission can affect other devices.

---

# 🚀 Future Improvements

Possible educational extensions include:

- Beacon-frame parser
- Wi-Fi packet visualization
- Controlled packet-rate measurement
- Wi-Fi scanner
- SSID encoding/decoding demonstration
- BSSID analysis
- Wireless anomaly detection
- Beacon-frame comparison tool
- Defensive detection of unusual beacon activity

---

# 📚 References

- Arduino IDE documentation
- Espressif Arduino-ESP32 documentation
- IEEE 802.11 wireless networking concepts

Official ESP32 installation documentation:

[Espressif Arduino-ESP32 Installation Guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html?utm_source=chatgpt.com)

Official ESP32 getting-started documentation:

[Espressif Arduino-ESP32 Getting Started](https://docs.espressif.com/projects/arduino-esp32/en/latest/getting_started.html?utm_source=chatgpt.com)

---

# 📜 License

This project can be released under the MIT License for educational and research use.

See [`LICENSE`](LICENSE) for details.

---

## ⚠️ Final Reminder

This repository is intended for **education, cybersecurity research, and authorized laboratory experimentation only**.

**Own the equipment. Own the network. Get permission before testing.**
