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
  char *Uname = "";
  char *Pass = "";

  MFRC522::MIFARE_Key key;
  for(byte i=0;i<6;i++) key.keyByte[i]=0xFF;

  byte block;
  byte len;

  MFRC522::StatusCode status;

  if(!mfrc522.PICC_IsNewCardPresent()){   //wait for card
    return;
  }
  if(!mfrc522.PICC_ReadCardSerial()){   //can the card be read from?
    return;
  }
  Serial.println(F("Card Detected.."));

  mfrc522.PICC_DumpToSerial(&mfrc522.uid); //Dump raw data

  byte buff_1[18]

  block=10;
  len=18;
/*
  Authenticate the card using Key A, and read the Username
*/
  status=mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 10, &key, &mfrc522.uid);   
  if(status != MFRC522::STATUS_OK){
    Serial.print("Authentication Failure: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buff_1, &len); //Read in Username
  if(status != MFRC522::STATUS_OK){
    Serial.print("Read Failure: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  for(uint8_t i=0;i<16;i++){
    if(buff_1[i]!=32){
      Serial.write(buff_1[i]);
    }
  }

  byte buff2[18];
  block=9;
  /*
    Authenticate the card using Key A and read the password
  */

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,9,&key,&mfrc522.uid);   //Auth keymode A
  if(status!=MFRC522::STATUS_OK){
    Serial.print("Authentication Failure: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buff2, &len);   //Read in the password
  if(status!=MFRC522:STATUS_OK){
    Serial.print("Read Failure: ");
    Searial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  for(uint8_t i=0;i<16; i++){
    Serial.write(buff2[i]);
  }

  Serial.println("Read Finished.");
  Serial.println("---------------");

  mfrc522.PICC_HaltA();
  mfrc522.PCD:StopCrypto1();

}
