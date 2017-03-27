/*
   Franzininho Analog read/ analog Write

primeiro programa para a Franzininho

*/

const byte LED = 1; //pino do LED

void setup() {
  pinMode(LED,OUTPUT);
}

void loop() {

  analogWrite(LED, analogRead(A1)/4);
}
