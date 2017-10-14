#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Display { // Objeto display
  private:
    LiquidCrystal_I2C &lcd;
    boolean luzFundo = HIGH;
  public:
    Display(LiquidCrystal_I2C &lcd, boolean luzFundo) {
      this->lcd = lcd; // Guardando referencia do display
      this->luzFundo = luzFundo;
    }
    Display(LiquidCrystal_I2C &lcd) {
      this->lcd = lcd;
    }
    void iniciar(const int x, const int y) const {
      lcd.begin(); // Inicializa o display LCD
      lcd.setBacklight(this->luzFundo); // Liga a luz de fundo do LCD
      lcd.setCursor(x, y);
      lcd.clear();
    }
    void iniciar() const {
      lcd.begin(); // Inicializa o display LCD
      lcd.setBacklight(this->luzFundo); // Liga a luz de fundo do LCD
      lcd.setCursor(0, 0);
      lcd.clear();  
    }
    void imprimir(const String msg) const {
      lcd.setCursor(0, 0);
      this->lcd.print(msg);
    }
    void imprimir(const String msg, const int x, const int y) const {
      lcd.setCursor(x, y);
      this->lcd.print(msg);
    }
    void apagarTudo() {
      lcd.clear();
      lcd.setCursor(2, 0);
    }
};
