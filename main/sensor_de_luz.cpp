/*
* 11/10/2017 
* Desenvolvido por DayvidCDS
* Backend com métodos para acionamento de reles via objeto, codificado em C++
*/

#include <Arduino.h>

class Ldr { // Objeto rele
  private:
    unsigned char pin; // Guarda o pino em que o LDR estará conectado
    unsigned char quantLuz; // Guarda o estado atual do rele (HIGH/LOW)
  public:
    Ldr(const unsigned char pin) { // Construtor, Método iniciado quando se cria a variável (Objeto)
      this->pin = pin; // Setando variável pin
    }
    int getLumen(int anaPin) {
      int anaValue = 0;
      for(int i = 0; i < 10; i++) {     
        anaValue += analogRead(anaPin);     
        delay(50);   
      }      
      anaValue = anaValue/10;  
      anaValue = map(anaValue, 1023, 0, 0, 100);
      return anaValue;  
    }
};
