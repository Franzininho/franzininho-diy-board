/*
   Franzininho Analog read/ analog Write

    Saida PWM através de entrada analógica

*/

const byte LED = 1; //pino do LED

void setup() {
  pinMode(LED,OUTPUT);
}

void loop() {

  analogWrite(LED, analogRead(A1)/4);
}
