#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5           
#define SS_PIN          10          

MFRC522 mfrc522(SS_PIN, RST_PIN);   

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  MFRC522::MIFARE_Key key;
  for(byte i=0;i<6;i++) key.keyByte[i]=0xFF;

  byte block;
  byte len;

  MFRC522::StatusCode status;

  if(!mfrc522.PICC_IsNewCardPresent()){
    return;
  }
  if(!mfrc522.PICC_ReadCardSerial()){
    return;
  }
  Serial.println(F("Card Detected.."));

  mfrc522.PICC_DumpToSerial(&mfrc522.uid); //Dump raw blocks

  byte buffer[18]

  block=10;
  len=18;

  status=mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 10, &key, &mfrc522.uid);
  if(status != MFRC522::STATUS_OK){
    Serial.print("Authentication Failure: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }


}
