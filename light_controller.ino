#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN     9
#define SS_PIN      10

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
MFRC522::MIFARE_Key key;

uint16_t solutions[3] = {2440, 52732, 65513};
uint16_t current_glyph = 0;
int correct = 0;
unsigned long time;

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

    if (current_glyph == solutions[0] || current_glyph == solutions[1] || current_glyph == solutions[2]){
      if (correct == 0 && time==0){
        digitalWrite(3, HIGH);
        Serial.println("FOUND 1");
        time = millis(); // start timer
        correct += 1;
      }
      else if (correct == 1 && (millis()-time) > 1000){
        digitalWrite(4, HIGH);
        Serial.println("FOUND 2");
        correct += 1;

      }
      else if (correct == 2 && (millis()-time) > 2000){
        digitalWrite(5, HIGH);
        Serial.println("FOUND 3");
        correct += 1;
      }
      else if (correct >= 3 && (millis()-time) > 3000){
        digitalWrite(6, HIGH);
        Serial.println("FOUND 4");
        /* correct += 1; */
      }
    }
    else{
      correct = 0;
      time = 0;
      Serial.println("RESET");
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }

}
