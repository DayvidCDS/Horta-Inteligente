#include <Arduino.h>

class Botao { // Objeto botao
  private:
    unsigned char pin; // Guarda o pino em que o botão estará conectado
  public:
    Botao(const unsigned char pin, const unsigned char acionamento) { // Construtor, Método iniciado quando se cria a variável (Objeto)
      this->pin = pin; // Setando variável pin
    }
    boolean ler() { // Ligando rele
      if (digitalRead(this->pin)) {
        return true;
      }
        return false;
    }
};
