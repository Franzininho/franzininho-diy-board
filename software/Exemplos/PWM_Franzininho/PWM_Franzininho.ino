/*
   Motor PWM
   Acionamento de Motor com PWM
   
   Por: Fábio Souza
*/


const int motorPin = 0;      

void setup() {
  pinMode(motorPin, OUTPUT);
}

void loop() {
  
    analogWrite(motorPin, (analogRead(1)/4));
  }

