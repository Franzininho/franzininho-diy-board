#include "DigiKeyboard.h"

void setup() {
  pinMode(1, OUTPUT);
}

void loop() {
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(500);
  DigiKeyboard.print("notepad");
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  DigiKeyboard.print(F("Ola, eu sou a Franzininho, uma placa compativel com Arduino."));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  DigiKeyboard.print(F("Acompanhe minhas aventuras seguindo minha pagina no Facebook "));
  DigiKeyboard.write(64);
  DigiKeyboard.print("franzininho");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  DigiKeyboard.print(F("Compartilhando Conhecimento"));
  DigiKeyboard.delay(100);

  while(1){
  digitalWrite(1,HIGH);
  delay(250);
  digitalWrite(1,LOW);
  delay(250);
    
  }
}
