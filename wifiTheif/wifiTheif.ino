// Libraries
#include <EEPROM.h>
#include "Keyboard.h"
#include "keyboardSeq.h"

// Define Input and Output Pins
int readWifiSwitch = 4;
int readWifiLight = 5;
int writeWifiSwitch = 6;
int writeWifiLed = 7;

//Address for EEPROM and space for string
int addr = 1;
char myString[999] = {""};

//Checking the state of a pushButton and low pass filtering
bool previousReadWifiButtonState = HIGH;   
bool buttonReadWifiState = HIGH;
bool previousWriteButtonState = HIGH;   
bool buttonWriteWifiState = HIGH;

// Used for Reducing noise on input pin
// lowPassInterations is ~1ms per interation
int lowPass = 0;  
int lowPassInterations = 100;

void setup() {
  //Begin Serial, Define IO
  Serial.begin(9600);
  pinMode(readWifiSwitch, INPUT);
  pinMode(writeWifiSwitch, INPUT);
  pinMode(readWifiLight, OUTPUT);
  pinMode(writeWifiLed, OUTPUT);
}

void loop() {
  // Read Instatatius State of the Input Pins
  bool noisyWifiSwitch = digitalRead(readWifiSwitch);
  bool noisyWriteSwitch = digitalRead(writeWifiSwitch);
//  Serial.print("noisyWifiSwitch:");
//  Serial.print(noisyWifiSwitch);
//  Serial.print("\t");
//  Serial.print("noisyWriteSwitch:");
//  Serial.println(noisyWriteSwitch);
  
  // Pin Noise Reduction 
  // Changes Button State after lowPass is greater the lowPassInterations
  if ((noisyWifiSwitch !=previousReadWifiButtonState)||(noisyWriteSwitch !=previousWriteButtonState) ){
    delay(1);
    lowPass++;
    if(lowPass > lowPassInterations){
      buttonReadWifiState = noisyWifiSwitch;
      buttonWriteWifiState = noisyWriteSwitch;
      lowPass = 0;
    }
  }

  // Condition for Starting Keyboard Sequences
  if (((buttonReadWifiState != previousReadWifiButtonState)) || ((buttonWriteWifiState != previousWriteButtonState)))
  {
    if(buttonReadWifiState == LOW){
      digitalWrite(readWifiLight,HIGH); //Turns On Indicator Light
      getWifiPasswords();
      Serial.println("here");
      // Writes String from the Serialport to the EEPROM
      for(int x; x<sizeof(myString) - 1; x++){
        myString[x] = Serial.read();
      }
      EEPROM.put(addr,myString);
      digitalWrite(readWifiLight,LOW); //Turns Off Indicator Light
    }
    if(buttonWriteWifiState == LOW){
      digitalWrite(writeWifiSwitch,HIGH); //Turns on Indicator Light
      // Writes EEPROM to Notepad
      writeWifiPasswords(EEPROM.get(addr, myString));
      digitalWrite(writeWifiSwitch,LOW); //Turns Off Indicator Light
    }
  }

  previousReadWifiButtonState = buttonReadWifiState;
  previousWriteButtonState = buttonWriteWifiState;
}
