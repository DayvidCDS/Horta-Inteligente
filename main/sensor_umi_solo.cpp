#include <Arduino.h>

class Solo { // Objeto Sensor de Umidade do Solo
  private:
    unsigned char pin; // Guarda o pino em que o Sensor estará conectado (Usar entradas analógicas)
    unsigned char vcc;
    unsigned char gnd;
   public:
    Solo(const unsigned char pin, unsigned char vcc, unsigned char gnd) { // Construtor, Método iniciado quando se cria a variável (Objeto)
      this->pin = pin; // Setando variável pin
      this->vcc = vcc;
      this->gnd = gnd;
    }
    int ler() {
      int anaValue;
      digitalWrite(this->vcc, LOW);
      digitalWrite(this->gnd, HIGH);
      delay(1000);
      anaValue = analogRead(this->pin); // Lendo valor analógico da porta setada no construtor
      digitalWrite(this->vcc, HIGH);
      digitalWrite(this->gnd, LOW);
      delay(1000);
      digitalWrite(this->vcc, LOW);
      anaValue = map(anaValue, 1023, 0, 0, 100);
      return anaValue;
    }
};
