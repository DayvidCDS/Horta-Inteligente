// Incluindo bibliotecas necessárias para o funcionamento do programa
#include "display.cpp";
#include "rele.cpp";
#include "sensor_de_luz.cpp";
#include "sensor_de_temp_umi.cpp";
#include "botao.cpp";

// Criando variáveis para o "contador global"
unsigned long tempoPassado = 0;
unsigned long tempoInicial = 0;
const unsigned long tempoDeAmostra = 30;

// Definições gerais
#define PIN_BOMBA 2
#define NIVEL_LOGICO_RELE_BOMBA LOW

#define DHTPIN 5 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

// Instanciando objetos
Rele bomba(PIN_BOMBA, NIVEL_LOGICO_RELE_BOMBA); // Instanciando o rele da bomba
DHT dhtParam(DHTPIN, DHTTYPE);
TempUmi dht(dhtParam); // Passando sensor DHT como parâmetro para o nosso objeto 

LiquidCrystal_I2C lcdParam(0x3F, 16, 2); // Instanciando Display LCD
Display lcd(lcdParam); // Passando como parâmetro o objeto lcdParam no objeto lcd

// cabeçalho das funções criadas neste arquivo
void calcularTempo(long *, long *, const long);

void setup() {
  lcd.iniciar();
  dhtParam.begin();
  pinMode(PIN_BOMBA, OUTPUT);
}

void loop() {
  // Aqui só implementa a lógica do sistema
  calcularTempo(&tempoInicial, &tempoInicial, tempoDeAmostra);
}

void calcularTempo(long *tempoPassado, long *tempoInicial, const long tempoAmostra) { // Função que calcula tempo que o arduino está ligado (Aconselhasse utilizar direto no loop)
  *tempoPassado = millis() - (*tempoInicial); // mensurando o tempo
  if (*tempoPassado > (tempoAmostra*1000)) {
    *tempoInicial = millis();
  }
}

