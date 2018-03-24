    /////////////////////////////////////////////////////////////////
   //                  Arduino RFID Tutorial               v1.02  //
  //       Get the latest version of the code here:              //
 //         http://educ8s.tv/arduino-rfid-tutorial/             //
/////////////////////////////////////////////////////////////////
#include <MFRC522.h>
#include <SPI.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
int pos = 0; 
Servo myservo; 
char password[4] = {'1','2','3','4'};
char pass[4];
int count = 0;
const byte ROWS = 2; // use 4X4 keypad for both instances
const byte COLS = 2;
char keys[ROWS][COLS] = {
  {'0','*'},
  {'8','7'}
};
byte rowPins[ROWS] = {25, 24}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {27,26}; //connect to the column pinouts of the keypad
Keypad kpd( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
const byte ROWSR = 2;
const byte COLSR = 2;
char keysR[ROWSR][COLSR] = {
  {'5','4'},
  {'2','1'}
};
byte rowPinsR[ROWSR] = {23, 22}; //connect to the row pinouts of the keypad
byte colPinsR[COLSR] = {27, 26}; //connect to the column pinouts of the keypad
Keypad kpdR( makeKeymap(keysR), rowPinsR, colPinsR, ROWSR, COLSR );
const byte ROWSUR = 4;
const byte COLSUR = 1;
char keysUR[ROWSUR][COLSUR] = {
  {'#'},
  {'9'},
  {'6'},
  {'3'}
};
// Digitran keypad, bit numbers of PCF8574 i/o port
byte rowPinsUR[ROWSUR] = {25, 24, 23, 22}; //connect to the row pinouts of the keypad
byte colPinsUR[COLSUR] = {28}; //connect to the column pinouts of the keypad
Keypad kpdUR( makeKeymap(keysUR), rowPinsUR, colPinsUR, ROWSUR, COLSUR );
const byte ROWL = 4;
const byte COLL = 1;
char keysL[ROWL][COLL] = {
  {'D'},
  {'C'},
  {'B'},
  {'A'}
};
// Digitran keypad, bit numbers of PCF8574 i/o port
byte rowPinsL[ROWL] = {25, 24, 23, 22}; //connect to the row pinouts of the keypad
byte colPinsL[COLL] = {29}; //connect to the column pinouts of the keypad
Keypad kpdL( makeKeymap(keysL), rowPinsL, colPinsL, ROWL, COLL );
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#define SS_PIN 53
#define RST_PIN 5
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
int code[] = {82,35,169,57}; //This is the stored UID
int codeRead = 0;
String uidString;
void setup() {
    kpdL.begin(makeKeymap(keysL));
  kpdUR.begin( makeKeymap(keysUR) );
  kpdR.begin( makeKeymap(keysR) );
  kpd.begin( makeKeymap(keys) );
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("RFID Lock");
  myservo.attach(6);
}
char key1, keyR, keyUR, keyL;
void loop() {
  if(  rfid.PICC_IsNewCardPresent())
  {
      readRFID();
      
  }
  delay(100);
      key1= kpd.getKey( );
  keyUR = kpdUR.getKey( );
  keyR = kpdR.getKey( );
  keyL = kpdL.getKey( );
  if (key1){
   //Serial.println(key1);
    pass[count] = key1;
    lcd.setCursor(count,1);
    lcd.print(key1);
    count++;
  }
  if( keyR ) {
   //Serial.println( keyR );
    pass[count] = keyR;
   lcd.setCursor(count,1);
    lcd.print(keyR);
    count++;
  }
  if( keyUR ) {
    //Serial.println( keyUR );
    pass[count] = keyUR;
    lcd.setCursor(count,1);
    lcd.print(keyUR);
    count++;
  }
  if(keyL){
    //Serial.println(keyL);
    pass[count] = keyL;
    lcd.setCursor(count,1);
    lcd.print(keyL);
    count++;
  }
  if(count >= 4){
    Serial.println(pass);
    if(pass[0] == password[0] && pass[1] == password[1] && pass[2] == password[2] && pass[3] == password[3] ){
      printUnlockMessage();
    }
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("         ");
   count = 0;
  }
}
void readRFID()
{
  
  rfid.PICC_ReadCardSerial();
  //Serial.print(F("\nPICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  //Serial.println(rfid.PICC_GetTypeName(piccType));
  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
  //  Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
    clearUID();
   
  //  Serial.println("Scanned PICC's UID:");
    printDec(rfid.uid.uidByte, rfid.uid.size);
    uidString = String(rfid.uid.uidByte[0])+" "+String(rfid.uid.uidByte[1])+" "+String(rfid.uid.uidByte[2])+ " "+String(rfid.uid.uidByte[3]);
    
    printUID();
    int i = 0;
    boolean match = true;
    while(i<rfid.uid.size)
    {
      if(!(rfid.uid.uidByte[i] == code[i]))
      {
           match = false;
      }
      i++;
    }
    if(match)
    {
     // Serial.println("\nI know this card!");
      printUnlockMessage();
    }else
    {
     // Serial.println("\nUnknown Card");
    }
    // Halt PICC
  rfid.PICC_HaltA();
  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
  Serial.println();
}
  void clearUID()
  {
    //lcd.setCursor(0,1); 
    //lcd.print(uidString);
  }
  void printUID()
  {
    //lcd.setCursor(0,1); 
    //lcd.print(uidString);
  }
  void printUnlockMessage()
  {
   // set the cursor to column 0, line 1
   // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 0);
    lcd.print("RFID Lock       ");
    
    lcd.setCursor(0, 0);
    lcd.print("RFID Unlocked");
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
                           // waits 15ms for the servo to reach the position
    }
    delay(2000);
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
                           // waits 15ms for the servo to reach the position
    }
    //delay(2000);
    lcd.setCursor(0, 0);
    lcd.print("RFID Lock       ");
  }

