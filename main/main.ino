// Incluindo bibliotecas necessárias para o funcionamento do programa

#include "display.cpp";
#include "rele.cpp";
#include "sensor_de_luz.cpp";
#include "sensor_de_temp_umi.cpp";
#include "botao.cpp";
#include "sensor_umi_solo.cpp";

// Criando variáveis para o "contador"

unsigned long tempoPassado = 0;
unsigned long tempoInicial = 0;
const unsigned long tempoDeAmostra = 30;

// Definições gerais

#define PIN_BOMBA 10
#define NIVEL_LOGICO_RELE_BOMBA LOW

#define DHTPIN 5
#define DHTTYPE DHT11 // DHT 11

#define SENSOR_UMI_SOLO1 A1
#define SENSOR_UMI_SOLO2 A2
#define SMS_VCC 7
#define SMS_GND 6

#define SENSOR_LUZ A0

// Instanciando objetos

Rele bomba1(PIN_BOMBA, NIVEL_LOGICO_RELE_BOMBA); // Instanciando o rele da bomba

DHT dhtParam(DHTPIN, DHTTYPE);
TempUmi dht(&dhtParam); // Passando sensor DHT como parâmetro para o nosso objeto
float temp, umi; // Variáveis para guardar temperatura e umidade

LiquidCrystal_I2C lcdParam(0x3F, 16, 2); // Instanciando Display LCD
Display lcd(&lcdParam); // Passando como parâmetro o objeto lcdParam no objeto lcd

Ldr ldr1(SENSOR_LUZ);

Solo solo1(SENSOR_UMI_SOLO1, SMS_VCC, SMS_GND);
Solo solo2(SENSOR_UMI_SOLO2, SMS_VCC, SMS_GND);

// cabeçalho das funções criadas neste arquivo

void calcularTempo(unsigned long *, unsigned long *, unsigned const long);

void setup() {
  lcd.iniciar();
  lcd.apagarTudo();
  lcd.imprimir("Iniciando Sensores...");
  dht.iniciar();
  pinMode(SMS_VCC,OUTPUT);
  pinMode(SMS_GND,OUTPUT); 
  pinMode(SENSOR_UMI_SOLO1, INPUT);
  pinMode(SENSOR_UMI_SOLO2, INPUT);
  pinMode(PIN_BOMBA, OUTPUT);
}

void loop() {
  // Aqui só implementa a lógica do sistema
  // calcularTempo(&tempoPassado, &tempoInicial, tempoDeAmostra);
  //dht.ler(&temp, &umi);
  //lcd.imprimir(ldr1.ler());
  
  int umiSolo = solo1.ler();
  
  lcd.imprimir(umiSolo);
  
  if (umiSolo < 70) {
    bomba1.ligar();
  }
  else {
    bomba1.desligar();  
  }
}

void calcularTempo(unsigned long *tempoPassado, unsigned long *tempoInicial, unsigned const long tempoAmostra) { // Função que calcula tempo que o arduino está ligado (Aconselhasse utilizar direto no loop)
  *tempoPassado = millis() - (*tempoInicial); // mensurando o tempo
  if (*tempoPassado > (tempoAmostra*1000)) {
    *tempoInicial = millis();
  }
}

