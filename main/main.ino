/*
* 11/10/2017 
* Desenvolvido por DayvidCDS
* Função principal, com a declaração das variáveis e chamada das funções necessárias
*/

// Incluindo bibliotecas necessárias para o funcionamento do programa
#include "rele.cpp";
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Criando variáveis para o "contador global"
unsigned long tempoPassado = 0;
unsigned long tempoInicial = 0;
unsigned long tempoDeAmostra = 30;

// Definições gerais
#define PIN_BOMBA 2
#define NIVEL_LOGICO_RELE_BOMBA LOW

#define DHTPIN 5 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

// Instanciando objetos
Rele bomba(PIN_BOMBA, NIVEL_LOGICO_RELE_BOMBA); // Instanciando o rele da bomba
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2); // Instanciando Display LCD

void lerTempUmi();

void setup() {
  lcd.begin(); // Inicializa o display LCD
  lcd.setBacklight(LOW); // Liga a luz de fundo do LCD
  lcd.setCursor(2, 0);
  lcd.clear();
  lcd.print("Iniciando...");
  delay(500);
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
  pinMode(PIN_BOMBA, OUTPUT);
}

void loop() {
  /*
  rele1.ligar();
  delay(1000);
  rele1.desligar();
  delay(1000);
  */
  lerTempUmi();
  delay(1500);
}

void lerTempUmi() {
  // A leitura da temperatura e umidade pode levar 250ms
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(t) || isnan(h)) { // testa se o retorno é valido
    Serial.println("Falha na leitura do DHT");
  } 
  else {
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
  }
}

