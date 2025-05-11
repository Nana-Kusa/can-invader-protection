/*
  CAN Autobaud Sniffer
  ---------------------
  A simple utility to detect the CAN bus baudrate automatically.
  Useful for initial setup of CAN shields and vehicle CAN analysis.

  Hardware: Arduino UNO + Seeed CAN-BUS Shield v2.0 (MCP2515 + TJA1050)
  Author: can-invader-protection project
  License: MIT
*/

#include <mcp_can.h>
#include <SPI.h>

const int SPI_CS_PIN = 9;
MCP_CAN CAN(SPI_CS_PIN);

// Try these baudrates in order
const long CAN_SPEEDS[] = {CAN_500KBPS, CAN_250KBPS, CAN_1000KBPS};
const char* SPEED_NAMES[] = {"500kbps", "250kbps", "1000kbps"};
const int NUM_SPEEDS = sizeof(CAN_SPEEDS) / sizeof(CAN_SPEEDS[0]);

void setup() {
  Serial.begin(115200);
  delay(1000);

  bool initialized = false;

  for (int i = 0; i < NUM_SPEEDS && !initialized; i++) {
    Serial.print("Trying ");
    Serial.print(SPEED_NAMES[i]);
    Serial.println("...");

    for (int attempt = 1; attempt <= 10 && !initialized; attempt++) {
      if (CAN_OK == CAN.begin(MCP_ANY, CAN_SPEEDS[i], MCP_8MHZ)) {
        Serial.print("CAN BUS Shield Init OK at ");
        Serial.println(SPEED_NAMES[i]);
        initialized = true;
      } else {
        Serial.print("Attempt ");
        Serial.print(attempt);
        Serial.println(" failed...");
        delay(500);
      }
    }
  }

  if (!initialized) {
    Serial.println("All baudrate attempts failed. Check wiring or vehicle.");
  }
}

void loop() {
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    unsigned long canId;
    byte len = 0;
    byte buf[8];
    CAN.readMsgBuf(&canId, &len, buf);

    Serial.print("ID: 0x");
    Serial.print(canId, HEX);
    Serial.print(" Data: ");
    for (int i = 0; i < len; i++) {
      if (buf[i] < 16) Serial.print("0");
      Serial.print(buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}
