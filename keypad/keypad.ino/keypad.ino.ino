#include <Keypad.h>

char pass[4];
int count = 0;
const byte ROWS = 2; // use 4X4 keypad for both instances
const byte COLS = 2;
char keys[ROWS][COLS] = {
  {'0','*'},
  {'8','7'}
};
byte rowPins[ROWS] = {5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6}; //connect to the column pinouts of the keypad
Keypad kpd( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


const byte ROWSR = 2;
const byte COLSR = 2;
char keysR[ROWSR][COLSR] = {
  {'5','4'},
  {'2','1'}
};
byte rowPinsR[ROWSR] = {3, 2}; //connect to the row pinouts of the keypad
byte colPinsR[COLSR] = {7, 6}; //connect to the column pinouts of the keypad
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
byte rowPinsUR[ROWSUR] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPinsUR[COLSUR] = {8}; //connect to the column pinouts of the keypad

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
byte rowPinsL[ROWL] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPinsL[COLL] = {9}; //connect to the column pinouts of the keypad

Keypad kpdL( makeKeymap(keysL), rowPinsL, colPinsL, ROWL, COLL );


void setup(){
//  Wire.begin( );
  kpdL.begin(makeKeymap(keysL));
  kpdUR.begin( makeKeymap(keysUR) );
  kpdR.begin( makeKeymap(keysR) );
  kpd.begin( makeKeymap(keys) );
  Serial.begin(9600);
  Serial.println( "start" );
}

//byte alternate = false;
char key, keyR, keyUR, keyL;
void loop(){

//  alternate = !alternate;
  key = kpd.getKey( );
  keyUR = kpdUR.getKey( );
  keyR = kpdR.getKey( );
  keyL = kpdL.getKey( );
  if (key){
   // Serial.println(key);
    pass[count] = key;
    count++;
  }
  if( keyR ) {
   // Serial.println( keyR );
    pass[count] = keyR;
    count++;
  }
  if( keyUR ) {
   // Serial.println( keyUR );
    pass[count] = keyUR;
    count++;
  }
  if(keyL){
   // Serial.println(keyL);
    pass[count] = keyL;
    count++;
  }
  if(count >= 4){
    Serial.println(pass);
   count = 0;
  }
}
