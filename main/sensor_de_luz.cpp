#include <Arduino.h>

class Ldr { // Objeto ldr
  private:
    unsigned char pin; // Guarda o pino em que o LDR estará conectado (Usar entradas analógicas)
    unsigned char valor;
  public:
    Ldr(const unsigned char pin) { // Construtor, Método iniciado quando se cria a variável (Objeto)
      this->pin = pin; // Setando variável pin
    }
    int ler() {
      int anaValue = 0;
      for(int i = 0; i < 10; i++) {     
        anaValue += analogRead(this->pin);
        delay(50);   
      }      
      anaValue = anaValue/10;  
      anaValue = map(anaValue, 1023, 0, 0, 100);
      this->valor = anaValue;
      return anaValue;  
    }
    unsigned char getValor() {
      return this->valor;
    }
};
