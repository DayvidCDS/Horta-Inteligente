#include "rele.cpp";

#define PIN_RELE1 2
#define NIVEL_LOGICO_RELE1 LOW

Rele rele1(PIN_RELE1, NIVEL_LOGICO_RELE1);

void setup() {
  pinMode(PIN_RELE1, OUTPUT);
}

void loop() {
  /*
  rele1.ligar();
  delay(1000);
  rele1.desligar();
  delay(1000);
  */
}
