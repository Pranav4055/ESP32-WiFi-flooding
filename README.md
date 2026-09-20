# ESP32 Wi-Fi Beacon Frame Research

> **Educational Cybersecurity & Embedded Systems Project**

An ESP32-based wireless-security research project for studying IEEE 802.11 Wi-Fi beacon frames and low-level Wi-Fi frame transmission.

---

## Disclaimer

**This project is strictly for educational purposes and authorized testing.**

- Use it only in your own controlled/isolated environment.
- Test only on your own ESP32 and Wi-Fi equipment.
- Do not interfere with or disrupt anyone else's network.
- Do not use it on public, college, office, airport, hotel, or third-party networks without explicit permission.
- Follow applicable wireless and radio regulations.

> **Use your own network. Do not harm or interfere with anyone else's network.**

---

## 📌 About the Project

This project demonstrates the use of an ESP32 for studying Wi-Fi beacon frames.

The project is designed to help beginners understand wireless protocols and embedded cybersecurity concepts using real ESP32 hardware.

### Main Topics

- ESP32 Wi-Fi
- IEEE 802.11
- Beacon frames
- SSID
- BSSID
- MAC addresses
- Unicode / UTF-8
- Wi-Fi channels
- Embedded C/C++

---

## 🛠️ Requirements

### Hardware

- ESP32 development board
- USB data cable
- Computer
- Controlled Wi-Fi testing environment

### Software

- Arduino IDE
- ESP32 board package

---

# 💻 Arduino IDE Installation

## Windows

Download Arduino IDE from the official Arduino website:

[Arduino IDE for Windows](https://www.arduino.cc/en/software/?utm_source=chatgpt.com)

### Installation

1. Download Arduino IDE.
2. Open the downloaded installer.
3. Follow the installation steps.
4. Open Arduino IDE.

---

## macOS

Download Arduino IDE from:

[Arduino IDE for macOS](https://www.arduino.cc/en/software/?utm_source=chatgpt.com)

### Installation

1. Download the macOS version.
2. Open the downloaded `.dmg` file.
3. Move Arduino IDE to the **Applications** folder.
4. Open Arduino IDE.

Arduino provides versions for both Intel and Apple Silicon Macs.

---

#  ESP32 Arduino IDE Configuration

## Step 1 — Open Preferences

Open Arduino IDE.

Go to:

```text
Arduino IDE
    ↓
Preferences / Settings
```

Find:

```text
Additional Boards Manager URLs
```

Add the official Espressif URL:

```text
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

Click **OK**.

---

#  Step 2 — Install ESP32 Board Package

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

---

#  Step 3 — Create a New Sketch

Open:

```text
File
   ↓
New Sketch
```

A new Arduino sketch will appear.

Open the project's:

```text
beacon_research.ino
```

Copy the code into the Arduino sketch.

---

#  Step 4 — Connect the ESP32

Connect your ESP32 to your computer using a **USB data cable**.

Make sure the board is properly connected.

---

#  Step 5 — Select Your ESP32 Board

Go to:

```text
Tools
   ↓
Board
   ↓
ESP32 Arduino
```

Select the **exact model of ESP32 you have**.

For example:

```text
ESP32 Dev Module
ESP32 DevKitC
ESP32-S3 Dev Module
ESP32-C3 Dev Module
```

> Select the board that matches your actual hardware.

---

#  Step 6 — Select the ESP32 Port

Go to:

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

or:

```text
/dev/cu.SLAB_USBtoUART
```

### Windows

It may look similar to:

```text
COM3
COM4
COM5
```

### If you cannot identify the port

1. Disconnect the ESP32.
2. Open **Tools → Port**.
3. Note the available ports.
4. Connect the ESP32.
5. Open **Tools → Port** again.
6. Select the newly appearing port.

---

#  Step 7 — Upload the Program

Make sure:

```text
Board → Your ESP32
Port  → Your ESP32 Port
```

are correctly selected.

Then click:

```text
Upload
```

Arduino IDE will compile and upload the program to the ESP32.

If your board requires it, press the **BOOT** button during the upload process.

---

#  Step 8 — Open Serial Monitor

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

Therefore the Serial Monitor must also use **115200 baud**.

---

#  Configuration

The main settings are located near the beginning of the Arduino program.

```cpp
const char *baseName = "student-wifi";
const uint8_t DIGITS = 6;
const uint8_t REPEATS = 10;
```

| Setting | Purpose |
|---|---|
| `baseName` | Base name used by the experiment |
| `DIGITS` | Number of Unicode-character positions |
| `REPEATS` | Number of repetitions |

---

#  Project Files

```text
ESP32-WiFi-Beacon-Research
│
├── README.md
├── beacon_research.ino
├── working.md
└── LICENSE
```

| File | Purpose |
|---|---|
| `README.md` | Project information and setup instructions |
| `beacon_research.ino` | Arduino ESP32 program |
| `working.md` | Technical explanation of the program |
| `LICENSE` | Project license |

---

# 🐛 Troubleshooting

### ESP32 board is not showing

- Check that ESP32 support is installed.
- Check that the correct board is selected.
- Restart Arduino IDE.

### ESP32 port is not showing

- Reconnect the USB cable.
- Use a USB data cable.
- Try another USB port.
- Install the required USB driver.
- Restart Arduino IDE.

### Upload fails

Check:

- Correct board
- Correct port
- USB connection
- USB data cable

If required, press the **BOOT** button during upload.

### Serial Monitor is showing incorrect output

Make sure the baud rate is:

```text
115200
```

---

# 🎓 Learning Objectives

This project helps demonstrate:

- ESP32 programming
- Wi-Fi fundamentals
- IEEE 802.11 concepts
- Beacon frames
- SSID and BSSID
- MAC addresses
- Unicode and UTF-8
- Wireless-security concepts
- Embedded systems

---

# 📚 References

[Arduino IDE](https://www.arduino.cc/en/software/?utm_source=chatgpt.com)

[Arduino-ESP32 Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/?utm_source=chatgpt.com)

---

# 📜 License

This project is intended for educational and authorized research purposes.

See `LICENSE` for more information.

---

## ⚠️ Responsible Use

**Use this project only on equipment and networks that you own or have explicit permission to test.**

The purpose of this project is education and cybersecurity research.
