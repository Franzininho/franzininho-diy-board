/*
   Robô Franzininho!
   
   Programa para robo controlado por Bluetooth
   
   Por: Fábio Souza
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 6); // RX, TX


const byte PIN_A = 0;
const byte PIN_B = 1;
const byte PIN_C = 3;
const byte PIN_D = 4;


void frente(){
  digitalWrite(PIN_A, HIGH);
  digitalWrite(PIN_B, LOW);
  digitalWrite(PIN_C, HIGH);
  digitalWrite(PIN_D, LOW);
}

void tras(){
  digitalWrite(PIN_A, LOW);
  digitalWrite(PIN_B, HIGH);
  digitalWrite(PIN_C, LOW);
  digitalWrite(PIN_D, HIGH);
}

void para(){
  digitalWrite(PIN_A, LOW);
  digitalWrite(PIN_B, LOW);
  digitalWrite(PIN_C, LOW);
  digitalWrite(PIN_D, LOW);
}

void direita(){
   digitalWrite(PIN_A, LOW);
  digitalWrite(PIN_B, HIGH);
  digitalWrite(PIN_C, HIGH);
  digitalWrite(PIN_D, LOW);
}

void esquerda(){
   digitalWrite(PIN_A, HIGH);
  digitalWrite(PIN_B, LOW);
  digitalWrite(PIN_C, LOW);
  digitalWrite(PIN_D, HIGH);
}

void setup() {
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);


  mySerial.begin(9600);

}

void loop() {

   if (mySerial.available()){

    
    int cmd = mySerial.read();
    if(cmd == 'a'){
     frente();
    }
    else if(cmd == 'b'){
      esquerda();
    }
    else if(cmd == 'd'){
      direita();
    }
     else if(cmd == 'e'){
      tras();
    }
    else if(cmd == 'c'){
      para();
    }
    
   }
   else{
    para(); 
   }
   delay(500);
  
}

