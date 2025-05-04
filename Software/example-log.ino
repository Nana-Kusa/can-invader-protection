/*
  example-log.ino - Simple CAN logger example
  For ESP32 + MCP2515 (SPI)
  Requires: mcp_can.h
*/

#include <mcp_can.h>
#include <SPI.h>

const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(115200);
  while (CAN_OK != CAN.begin(CAN_500KBPS)) {
    Serial.println("CAN init failed, retrying...");
    delay(100);
  }
  Serial.println("CAN init success");
}

void loop() {
  unsigned char len = 0;
  unsigned char buf[8];
  unsigned long id;

  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    id = CAN.getCanId();
    CAN.readMsgBuf(&len, buf);

    Serial.print("ID: 0x");
    Serial.print(id, HEX);
    Serial.print(" Data: ");
    for (int i = 0; i < len; i++) {
      Serial.print(buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}
