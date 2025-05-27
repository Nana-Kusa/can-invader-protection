/*
  CAN Logger with microSD (Buffered)
  ----------------------------------
  Logs CAN traffic to microSD card with write buffering.
  Stops automatically after receiving 10000 messages.
  Enters power-down sleep mode after logging.

  Hardware:
    - Arduino UNO
    - Seeed CAN-BUS Shield v2.0 (MCP2515 + TJA1050)
    - microSD card via SPI (CS pin 4)
    - Mitsubishi ek Wagon
*/

#include <SPI.h>
#include <SD.h>
#include "mcp2515_can.h"
#include <avr/sleep.h> // スリープ機能を使うために必要 // Required for sleep functionality

// CANバスとSDカードのSPI CSピン定義 // SPI CS pin definitions for CAN bus and SD card
const int SPI_CS_CAN = 9;
const int SPI_CS_SD  = 4;

// ログファイルをフラッシュするメッセージ間隔 // Message interval to flush the log file
const int FLUSH_INTERVAL = 5;

// MCP2515 CANコントローラオブジェクト // MCP2515 CAN controller object
mcp2515_can CAN(SPI_CS_CAN);

// SDカードファイルオブジェクト // SD card file object
File logfile;

// ログファイル名と最大メッセージ数 // Log file name and maximum message count
#define LOG_FILE_NAME "canlog3.txt"
#define MAX_MESSAGES 10000

// 受信メッセージカウンター // Received message counter
unsigned int message_count = 0;

// --- 終了処理とパワーダウンスリープモードへの移行を行う関数 ---
// Function to handle termination and transition to power-down sleep mode
void enterSleepMode() {
  Serial.println("Entering power-down sleep mode.");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  cli();
  sleep_cpu();
  sleep_disable();
  sei();
}

void StartCoundDown(){
    Serial.println("3"); delay(1000); 
    Serial.println("2"); delay(1000); 
    Serial.println("1"); delay(1000); 
    Serial.println("start!");
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  if (!SD.begin(SPI_CS_SD)) {
    Serial.println("SD init failed! Entering sleep mode.");
    enterSleepMode();
  }
  Serial.println("SD init ok!");

  logfile = SD.open(LOG_FILE_NAME, FILE_WRITE);
  if (!logfile) {
    Serial.println("Failed to open file on SD! Entering sleep mode.");
    enterSleepMode();
  }
  Serial.println("Log file opened.");
  logfile.println("Timestamp, ID, Type, Data");

  while (CAN_OK != CAN.begin(CAN_500KBPS)) {
    Serial.println("CAN init fail, retry...");
    delay(100);
  }
  Serial.println("CAN init ok!");
  logfile.println("CAN init ok!");
  StartCoundDown();
}

void loop() {
  if (message_count >= MAX_MESSAGES) {
    Serial.println("Max message count reached. Stopping and entering sleep mode.");
    logfile.println("Max message count reached. Stopping.");
    logfile.flush();
    logfile.close();
    enterSleepMode();
  }

  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    byte len = 0;
    byte buf[8];
    CAN.readMsgBuf(&len, buf);

    unsigned long canId = CAN.getCanId();
    byte type = (CAN.isExtendedFrame() << 0) | (CAN.isRemoteRequest() << 1);
    static const byte type2[] = {0x00, 0x02, 0x30, 0x32};
    unsigned long t = millis();

    char line[128];
    int n = snprintf(line, sizeof(line), "%04lu.%03lu, %08lX, %02X, ",
                     t / 1000, t % 1000, canId, type2[type]);
    for (int i = 0; i < len; i++) {
      n += snprintf(line + n, sizeof(line) - n, "%02X ", buf[i]);
    }

    // 省略対象のIDとデータの条件チェック // Skip condition check for specific ID and data patterns
    // Mitsubishi ek Wagon's codes.
    bool skip = false;
    if (canId == 0x00000101 && len == 1 && buf[0] == 0x04) {
      skip = true;
    } else if (canId == 0x00000255 && len == 8 &&
               buf[0] == 0x3F && buf[1] == 0xFF && buf[2] == 0x3F && buf[3] == 0xFF &&
               buf[4] == 0x3F && buf[5] == 0xFF && buf[6] == 0xFF && buf[7] == 0xFF) {
      skip = true;
    } else if (canId == 0x00000265 && len == 8 &&
               buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x00 && buf[3] == 0x00 &&
               buf[4] == 0xFF && buf[5] == 0xFF && buf[6] == 0x07 && buf[7] == 0xD3) {
      skip = true;
    } else if (canId == 0x00000520 && len == 8 &&
               buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x00 && buf[3] == 0x00 &&
               buf[4] == 0x00 && buf[5] == 0x00 && buf[6] == 0x00 && buf[7] == 0x00) {
      skip = true;
    } else if (canId == 0x00000424 && len == 8 &&
               buf[0] == 0x98 && buf[1] == 0x00 && buf[2] == 0x04 && buf[3] == 0x01 &&
               buf[4] == 0xC1 && buf[5] == 0xBE && buf[6] == 0x00 && buf[7] == 0x00) {
      skip = true;
    }

    if (!skip) {
      logfile.println(line);
      message_count++;
      if (message_count % FLUSH_INTERVAL == 0) {
        logfile.flush();
        Serial.print("Flushed buffer. Message count: ");
        Serial.println(message_count);
      }
    }
  }
}
