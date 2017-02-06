#include <SPI.h>
#include <MFRC522.h>
#include <Time.h>

#define RST_PIN     9      
#define SS_PIN      10      

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
MFRC522::MIFARE_Key key;

uint16_t solution = 2440;  // mfrc522.uid.size
uint16_t current_glyph = 0;
int correct = 0;

void setup()
{
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));


  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

}


uint16_t read_card() {
  uint16_t xor_uid = 0;
  
  if (! mfrc522.PICC_ReadCardSerial()) 
    { 
      current_glyph = 0;
    }
  else 
  {    
    for (int i = 0; i < mfrc522.uid.size; i=i+2) 
    {  
      current_glyph = xor_uid ^ (mfrc522.uid.uidByte[i]<<8 | mfrc522.uid.uidByte[i+1]);
    }
    Serial.println(current_glyph);
  }
  return current_glyph;
}

void loop()
{
  
  mfrc522.PICC_ReadCardSerial(); //Always fails
  mfrc522.PICC_IsNewCardPresent(); //Does RequestA 
  current_glyph = read_card();


  if (current_glyph == solution){
    Serial.println("FOUND");
    Serial.println(now());
    
    if (correct == 1){
      digitalWrite(3, HIGH);
    }
    else if (correct == 2){
      digitalWrite(4, HIGH);
    }
    else if (correct == 3){
      digitalWrite(5, HIGH);
    }
    else if (correct == 4){
      digitalWrite(6, HIGH);
    }
    
    correct += 1;
  }
  else{
    correct = 0;
  }
  
  delay(1000);
}


