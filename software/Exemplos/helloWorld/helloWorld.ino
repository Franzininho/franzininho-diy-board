/*
   Hello World, Franzininho!

primeiro programa para a Franzininho

*/

const byte LED = 1; //pino do LED

void setup() {
  pinMode(LED,OUTPUT);
}

void loop() {

  for(int i = 0;i<5;i++)       //pisca o LED 5 vezes com instervalos de 100 ms
  {
    digitalWrite(LED, HIGH);   // liga o led
    delay(100);                // espera 100 ms
    digitalWrite(LED, LOW);    // apaga led
    delay(100);                // espera 100 ms
  }

  for(int i = 0;i<2;i++)       //pisca o LED 2 vezes com instervalos de 1000 ms
  {
    digitalWrite(LED, HIGH);   // liga o led
    delay(1000);                // espera 1000 ms
    digitalWrite(LED, LOW);    // apaga led
    delay(1000);                // espera 1000 ms
  }
}
