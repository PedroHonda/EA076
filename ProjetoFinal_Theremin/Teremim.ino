#include <MFRC522.h>
#include <SPI.h>
/* PIN DEFINITION */
// Sensor IR
#define sensorIR A0
// Sensor Ultrassônico
#define trigPIN 7
#define echoPIN 6
// Pinos para o leitor RFID
#define SDA_RFID 10
#define RST_RFID 9
// Buzzer
#define buzzerPIN 5
// Volume
#define v1PIN 4
#define v2PIN 3
#define v3PIN 2


MFRC522 rfid(SDA_RFID, RST_RFID);
MFRC522::MIFARE_Key key; 

/* GLOBAL VARIABLES DEFINITION */
float volAnalog, volInv, volPrevious;
int volumeState = 0;

long duration, distance, freqCurrent,freqPrevious;
long note;
// RFID
String RFID_code; // String para armazenar o valor obtido da leitura do RFID card/tag
int isRFID = 0; // flag

void setup() {
  // RFID init
  SPI.begin();
  rfid.PCD_Init();
  // Sensor de proximidade ultrassonico
  pinMode(trigPIN, OUTPUT);
  pinMode(echoPIN, INPUT);
  // Pino da alimentação do buzzer
  pinMode(buzzerPIN, OUTPUT);
  // Pino de controle de volume
  pinMode(v1PIN, OUTPUT);       
  pinMode(v2PIN, OUTPUT);
  pinMode(v3PIN, OUTPUT);
  digitalWrite(v1PIN, HIGH);
  digitalWrite(v2PIN, HIGH);
  digitalWrite(v3PIN, HIGH);
  Serial.begin(9600);
  freqPrevious = 0;
  volPrevious = 0;
}

void loop() {
/*MIFARE 1KB
32 194 163 124 ---- Cartao
MIFARE 1KB
32 58 196 128 ---- Azul
*/
  if (rfid.PICC_IsNewCardPresent()) {
    rfid.PICC_ReadCardSerial();
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    RFID_code = String(rfid.uid.uidByte[0])+" "+String(rfid.uid.uidByte[1])+" "+String(rfid.uid.uidByte[2])+ " "+String(rfid.uid.uidByte[3]);
    //Serial.println(rfid.PICC_GetTypeName(piccType));
    Serial.println(RFID_code);

    if ((rfid.uid.uidByte[0] == 32) && (rfid.uid.uidByte[1] == 58) && (rfid.uid.uidByte[2] == 196) &&(rfid.uid.uidByte[3] == 128)) {
      if (isRFID) {
        isRFID = 0;
        noTone(buzzerPIN);
      }
      else {
        isRFID = 1;
      }
      digitalWrite(v1PIN, LOW);
      digitalWrite(v2PIN, LOW);
      digitalWrite(v3PIN, LOW);
      delay(150);
      digitalWrite(buzzerPIN, HIGH);
      delay(150);
      digitalWrite(buzzerPIN, LOW);
      delay(150);
      digitalWrite(buzzerPIN, HIGH);
      delay(150);
      digitalWrite(buzzerPIN, LOW);
      delay(150);
      digitalWrite(buzzerPIN, HIGH);
      delay(150);
      digitalWrite(buzzerPIN, LOW);
      delay(150);
    }
    else {
      digitalWrite(v1PIN, LOW);
      digitalWrite(v2PIN, LOW);
      digitalWrite(v3PIN, LOW);
      delay(150);
      digitalWrite(buzzerPIN, HIGH);
      delay(150);
      digitalWrite(buzzerPIN, LOW);
      delay(150);
    }
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

  if (isRFID) {
    theremin();
  }
}

void theremin() {
  digitalWrite(trigPIN, LOW);
  // 10us trigger
  delayMicroseconds(5);
  digitalWrite(trigPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPIN, LOW);
  // calculating distance
  duration = pulseIn(echoPIN, HIGH);
  distance = duration * 0.017;
  freqCurrent = map(duration, 100, 3000, 500, 700);

  if (freqCurrent > 700) freqCurrent = 700;
  else if (freqCurrent < 500) freqCurrent = 500;

 
  if (freqPrevious) {
    if ((freqPrevious < (freqCurrent + 30)) || (freqPrevious > (freqCurrent - 30))) {
      tone(buzzerPIN,freqPrevious);
    }
  }

  freqPrevious = freqCurrent;

  
  volAnalog = analogRead(sensorIR);
  volInv = 100000/volAnalog;

  /*if (volPrevious) {
    if ((volPrevious < (volInv + 10)) || (freqPrevious > (volInv - 10))) {
      volInv = volPrevious;
    }
  }*/
  Serial.println(volumeState);
  switch(volumeState) {
    case 0:
      digitalWrite(v1PIN, LOW);
      digitalWrite(v2PIN, LOW);
      digitalWrite(v3PIN, LOW);
      if (volInv > 200) volumeState = 1;
      break;
    case 1:
      digitalWrite(v1PIN, LOW);
      digitalWrite(v2PIN, LOW);
      digitalWrite(v3PIN, HIGH);
      if (volInv < 160) volumeState = 0;
      else if (volInv > 300) volumeState = 2;
      break; 
    case 2:
      digitalWrite(v1PIN, HIGH);
      digitalWrite(v2PIN, HIGH);
      digitalWrite(v3PIN, HIGH);
      if (volInv < 260) volumeState = 1;
      break;
  }
  
/*  switch(volumeState) {
    case 0:
      digitalWrite(v1PIN, LOW);
      digitalWrite(v2PIN, LOW);
      digitalWrite(v3PIN, LOW);
      if (volInv > 185) volumeState = 1;
      break;
    case 1:
      digitalWrite(v1PIN, LOW);
      digitalWrite(v2PIN, LOW);
      digitalWrite(v3PIN, HIGH);
      if (volInv < 177) volumeState = 0;
      else if (volInv > 222) volumeState = 2;
      break; 
    case 2:
      digitalWrite(v1PIN, LOW);
      digitalWrite(v2PIN, HIGH);
      digitalWrite(v3PIN, HIGH);
      if (volInv < 214) volumeState = 1;
      else if (volInv > 280) volumeState = 3;
      break;
    case 3:
      digitalWrite(v1PIN, HIGH);
      digitalWrite(v2PIN, HIGH);
      digitalWrite(v3PIN, HIGH);
      if (volInv < 272) volumeState = 2;
      break;
  }*/

  volPrevious = volInv;
}

