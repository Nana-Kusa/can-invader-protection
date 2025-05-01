# CAN Invader Protection

An open-source lightweight CAN bus intrusion detection and defense system for personal vehicle security.

👉 [日本語READMEはこちら (Japanese README)](README.ja.md)

---

## Purpose

This project aims to defend against CAN bus-based vehicle theft attacks, commonly known as "CAN Invader" attacks, by detecting unauthorized unlock signals and automatically triggering a re-lock or alarm.

---

## Features

- Real-time detection of unauthorized door unlock attempts via CAN bus  
- Automatic re-lock when unauthorized signals are detected  
- Horn alarm triggered upon repeated suspicious attempts  
- Time-based defense mode (e.g., enhanced protection at night)  
- Designed for low-cost, readily available hardware components  
- Non-intrusive installation: no need to modify vehicle systems  

---

## Hardware Requirements

- ESP32 development board  
- MCP2515 CAN bus transceiver module  
- OBD-II splitter cable (or direct CAN wiring)  
- 12V to 5V DC-DC converter for stable power supply  

---

## Software

- Compatible with Arduino IDE  
- Lightweight CAN message monitoring and reactive transmission logic  

---

## Installation

1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Clone this repository:
   ```bash
   git clone https://github.com/Nana-Kusa/can-invader-protection.git
   ```
3. Open the sketch in `Software/` using the Arduino IDE.
4. Install required libraries (e.g., `mcp_can.h`).
5. Connect your board and upload the code.

---

## Directory Structure

```text
can-invader-protection/
├── README.md
├── README.ja.md
├── Docs/
│   ├── vision.md
│   ├── usage.md
│   └── usage.ja.md
├── Hardware/
│   └── parts-list.md
└── Software/
    └── empty.ino
```

---

## Documentation

Further technical documentation will be available in the [Wiki](https://github.com/Nana-Kusa/can-invader-protection/wiki) (coming soon).

---

## Contributing

Contributions are welcome!  
Please open an [Issue](https://github.com/Nana-Kusa/can-invader-protection/issues) or submit a [Pull Request](https://github.com/Nana-Kusa/can-invader-protection/pulls).  
A contribution guide ([CONTRIBUTING.md](CONTRIBUTING.md)) will be provided in the future.

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Disclaimer

Use at your own risk. This system enhances vehicle security but does not guarantee full protection against all threats.
