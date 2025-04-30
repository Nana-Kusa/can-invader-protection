# CAN Invader Protection

An open-source lightweight CAN bus intrusion detection and defense system for personal vehicle security.


[日本語READMEはこちら](README.ja.md)

## Purpose

This project aims to defend against CAN bus-based vehicle theft attacks, commonly known as "CAN Invader" attacks, by detecting unauthorized unlock signals and automatically responding.

## Features

- Real-time detection of door unlock attempts on the CAN bus
- Automatic re-locking upon detecting unauthorized unlocks
- Horn alarm triggering upon repeated suspicious unlock attempts
- Time-based defense mode (e.g., stronger protection during nighttime)
- Designed for low-cost, easily available hardware components
- Simple setup without modifying the vehicle's existing systems

## Hardware Requirements

- ESP32 development board
- MCP2515 CAN bus transceiver module
- OBD-II splitter cable (or direct CAN wiring)
- 12V to 5V DC-DC converter (for stable power supply)

## Software

- Arduino IDE compatible code
- Lightweight CAN message monitoring and reactive transmission

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Disclaimer

Use at your own risk. This system is intended to enhance security but cannot guarantee complete protection against all attacks.

