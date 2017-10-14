#include <Arduino.h>

class Rele { // Objeto rele
  private:
    unsigned char pin; // Guarda o pino em que o rele estará conectado
    unsigned char acionamento; // Guarda a forma de acionaemnto do rele (HIGH/LOW)
    volatile unsigned char estado; // Guarda o estado atual do rele (HIGH/LOW)
  public:
    Rele(const unsigned char pin, const unsigned char acionamento) { // Construtor, Método iniciado quando se cria a variável (Objeto)
      this->pin = pin; // Setando variável pin
      this->acionamento = acionamento; // Setando variável acionamento
      this->desligar(); // Aqui desligamos o rele para evitar problemas
    }
    void ligar() { // Ligando rele
      this->estado = this->acionamento; // Modificando o valor da variável "estado"
      digitalWrite(this->pin, this->estado);
    }
    void desligar() { // Desligando rele
      this->estado = !(this->acionamento); // Modificando o valor da variável "estado", aqui pegamos o inverso de acionamento
      digitalWrite(this->pin, this->estado);
    }
};
