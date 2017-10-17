#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Display { // Objeto display
  private:
    LiquidCrystal_I2C *lcd;
    boolean luzFundo = HIGH;
  public:
    Display(LiquidCrystal_I2C *lcd, boolean luzFundo) {
      this->lcd = lcd; // Guardando referencia do display
      this->luzFundo = luzFundo;
    }
    Display(LiquidCrystal_I2C *lcd) {
      this->lcd = lcd;
    }
    void iniciar(const int x, const int y) const {
      this->lcd->begin(); // Inicializa o display LCD
      this->lcd->setBacklight(this->luzFundo); // Liga a luz de fundo do LCD
      this->lcd->setCursor(x, y);
      this->lcd->clear();
    }
    void iniciar() const {
      this->lcd->begin(); // Inicializa o display LCD
      this->lcd->setBacklight(this->luzFundo); // Liga a luz de fundo do LCD
      this->lcd->setCursor(0, 0);
      this->lcd->clear();  
    }
    void imprimir(const byte msg) const {
      this->lcd->setCursor(0, 0);
      this->lcd->print(msg);
    }
    void imprimir(const byte msg, const int x, const int y) const {
      this->lcd->setCursor(x, y);
      this->lcd->print(msg);
    }
    void apagarTudo() {
      this->lcd->clear();
      this->lcd->setCursor(2, 0);
    }
    void setLuzFundo(boolean estado) {
      this->luzFundo = estado;
      this->lcd->setBacklight(this->luzFundo);
    }
};
