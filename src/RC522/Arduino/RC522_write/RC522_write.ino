#include<SPI.h>
#include<MFRC522.h>

#define RST_PIN 5
#define SS_PIN 53

MFRC522 mfrc522(SS_PIN,RST_PIN);

void setup(){
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  if(!mfrc522.PICC_IsNewCardPresent()){   //wait for card
    return;
  }
  if(!mfrc522.PICC_ReadCardSerial()){   //can the card be read from?
    return;
  }

  Serial.print("Card UID: ");
  for(byte i = 0; i<mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i]<0x10?" 0":" ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }

  Serial.print(" PICC type: ");   // Dump PICC type
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));

  byte buffer[34];
  byte block;
  byte len;

  MFRC522::StatusCode status;

  Serial.setTimeout(20000L);

  Serial.println("Type username, ending with #");
  len=Serial.readBytesUntil('#', (char*)buffer, 30);
  for(byte i = len;i<30;i++) buffer[i] = ' ';

  block = 1;
  
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Authentication Failure: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Write(block, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Failure writing to block: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  block=2;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Authentication Failure: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Write(block, &buffer[16], 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Failure Writing to block: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //Password


  Serial.println(F("Type Password, ending with #"));
  len = Serial.readBytesUntil('#', (char *) buffer, 20) ; 
  for (byte i = len; i < 20; i++) buffer[i] = ' ';     

  block = 4;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Authentication Failure: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Write(block, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Failure Writing to block: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  block = 5;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("PCD_Authenticate() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }


  status = mfrc522.MIFARE_Write(block, &buffer[16], 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Failure Writing to block: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }


  Serial.println(" ");
  mfrc522.PICC_HaltA(); // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
}
