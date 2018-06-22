#include <MFRC522.h>
#include <SPI.h>
#define sensorIR A0 // sensor IR
#define SDA_RFID 10
#define RST_RFID 9
 
MFRC522 rfid(SDA_RFID, RST_RFID);
MFRC522::MIFARE_Key key; 

int trigPIN = 7;
int echoPIN = 6;
int buzzerPIN = 5;
int testPIN = 0;
int volumeControlPIN1 = 4;
float volumeF;
float volumeD;

long duration, distance, freq1,freq2;
long note;

// RFID
String RFID_code;
int isRFID = 0;

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
  pinMode(volumeControlPIN1, OUTPUT);       
  digitalWrite(volumeControlPIN1, LOW);
  Serial.begin(9600);
  freq2 = 0;
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
  freq1 = map(duration, 100, 3000, 500, 700);

  if (freq1 > 700) freq1 = 700;
  else if (freq1 < 500) freq1 = 500;

  volumeF = analogRead(sensorIR);
  volumeD = 9462/(volumeF - 16.92);

  if (volumeD < 30) {
    digitalWrite(volumeControlPIN1, HIGH);
  }
  else {
    digitalWrite(volumeControlPIN1, LOW);
  }
 
  //freq1 = volumeD*20;
  if (freq2) {
    if ((freq2 < (freq1 + 50)) || (freq2 > (freq1 - 50))) {
      tone(buzzerPIN,freq2);
    }
    
  }
  
  freq2 = freq1;
}

