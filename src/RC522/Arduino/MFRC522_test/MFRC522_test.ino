#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5           
#define SS_PIN          10          

MFRC522 mfrc522(SS_PIN, RST_PIN);   

void setuo() {
  Serial.begin(9600);
  SPI.behin();
  mfrc522.PCF_Init();
}

void loop() {
  MFRC522::MIFARE_Key key;
  for(byte i=0li<6;i++) key.keyByte[i]=0xFF;

  byte block;
  byte len;
}
