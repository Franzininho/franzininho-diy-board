/*
   Teste Bluetooth usando softserial
   
   Por: Fábio Souza
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {

  pinMode(1, OUTPUT);
   // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

   if (mySerial.available()){

    
    int cmd = mySerial.read();
    if(cmd == 'f'){
      digitalWrite(1, HIGH);
    }
    else if(cmd == 'g'){
      digitalWrite(1, LOW);
    }
   }
   delay(500);
  
}

