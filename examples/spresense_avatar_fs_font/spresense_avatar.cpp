#include <Arduino.h>
#include <Display.h>
#include <Avatar.h>

#define _USE_FS_FONT // ファイルシステム版フォントを使うか
#ifdef _USE_FS_FONT
#include <SDHCI.h>
#include "FS_U8g2font.h"
SDClass SD;             // SDカード
lgfx::FS_U8g2font font; // ファイルシステム版フォント
int sdcard_reset();     // SDカードリセット (自作基板の設計ミスのため)
#endif

#define TFT_BL        9 // バックライトのピン

using namespace m5avatar;

Avatar avatar;

void setup()
{
  ledOn(LED0);
  Display.begin();
  Display.setRotation(3);     // 画面回転(横向き)
//Display.setBrightness(255); // バックライト100%(全点灯)
  Display.fillScreen(TFT_BLACK);

  Serial.begin(115200);
// while(!Serial){;}

#ifdef _USE_FS_FONT
#ifdef _USE_FS_FONT
  int ret = sdcard_reset();
  if(ret < 0) {
      Serial.println("SD card reset failed");
  }else{
    ledOff(LED0);
  }
#endif
  ledOn(LED1);
  while(!SD.begin()) {
      Serial.print("."); usleep(500*1000);
  }
  usleep(500*1000);
  
  //delay(3000);
  ledOn(LED3);

  if(font.loadFont("/mnt/sd0/fs_efont_ja_16.bin") != true)
  {
    Serial.println("Font load error!");
    ledOff(LED3);
  }
  font.loadGlyph("国破山河在");
#endif
  ledOff(LED2);
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH); // バックライトON

  avatar.init(); // start drawing
  ledOff(LED1);

#ifdef _USE_FS_FONT
  avatar.setSpeechFont(&font);
#else
  avatar.setSpeechFont(&fonts::efontJA_16);
#endif
  
  avatar.setSpeechText("こんにちは");
  ledOff(LED0);
}

char* strdata[]={
  "葡萄美酒夜光杯",
  "欲飲琵琶馬上催",
  "酔臥沙場君莫笑",
  "古来征戦幾人回"
};
int cnt = 0;

void loop()
{
  usleep(1000*1000);
  avatar.setSpeechText("Hello!");

  usleep(1000*1000);
  avatar.setSpeechText("国破山河在");

  usleep(1000*1000);
  avatar.setSpeechText("こんにちは");
/*
  usleep(1000*1000);
  font.loadGlyphCache(strdata[cnt]);
  avatar.setSpeechText(strdata[cnt]);
  cnt = (cnt + 1) % 4;
*/
}
