# CAN Autobaud Sniffer Example

This example automatically detects the baudrate of the connected CAN bus and starts listening to CAN traffic.

## Hardware Requirements

- Arduino UNO (or compatible)
- Seeed Studio CAN-BUS Shield v2.0 (MCP2515 + TJA1050)
- MCP_CAN library
- Vehicle or test CAN network

## Description

The sketch tries standard CAN speeds (500kbps, 250kbps, 1000kbps) and selects the first one that initializes successfully.  
Then it continuously prints received CAN frames over the serial monitor (115200 baud).

## Usage

1. Connect CAN shield to Arduino.
2. Upload the sketch.
3. Open serial monitor at 115200 baud.
4. Check the detected baudrate and observe CAN frames.

## Notes

- This is intended as a setup and troubleshooting utility.
- You can modify `CAN_SPEEDS[]` array to test additional baudrates.
- Currently set for Seeed Studio CAN-BUS Shield v2.0 with SPI_CS_PIN = 9 and MCP_8MHZ.

## License

MIT License. See LICENSE file.
