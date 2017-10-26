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

#define PIN_SOLENOIDE1 8 // Solenoide da caixa
#define NIVEL_LOGICO_RELE_SOLENOIDE1 LOW

#define PIN_SOLENOIDE2 9 // Solenoide das plantas
#define NIVEL_LOGICO_RELE_SOLENOIDE2 LOW

#define DHTPIN 5
#define DHTTYPE DHT11 // DHT 11

#define SENSOR_UMI_SOLO1 A1
#define SENSOR_UMI_SOLO2 A2
#define SENSOR_UMI_SOLO3 A3
#define SMS_VCC 7
#define SMS_GND 6

#define SENSOR_LUZ A0
#define NOITE 30

#define SOLO_SECO 40
#define SOLO_UMIDO 60

// Instanciando objetos

Rele bomba(PIN_BOMBA, NIVEL_LOGICO_RELE_BOMBA); // Instanciando o rele da bomba
Rele solenoide_caixa(PIN_SOLENOIDE1, NIVEL_LOGICO_RELE_SOLENOIDE1);
Rele solenoide_plantas(PIN_SOLENOIDE2, NIVEL_LOGICO_RELE_SOLENOIDE2);

DHT dhtParam(DHTPIN, DHTTYPE);
TempUmi dht(&dhtParam); // Passando sensor DHT como parâmetro para o nosso objeto
float temp, umi; // Variáveis para guardar temperatura e umidade

LiquidCrystal_I2C lcdParam(0x3F, 16, 2); // Instanciando Display LCD
Display lcd(&lcdParam); // Passando como parâmetro o objeto lcdParam no objeto lcd

Ldr ldr1(SENSOR_LUZ);

Solo solo1(SENSOR_UMI_SOLO1, SMS_VCC, SMS_GND);
Solo solo2(SENSOR_UMI_SOLO2, SMS_VCC, SMS_GND);
Solo solo3(SENSOR_UMI_SOLO3, SMS_VCC, SMS_GND);

// cabeçalho das funções criadas neste arquivo

void calcularTempo();
void liberarSolucao();
int lerSensores();
void agitarSolucao();

void setup() {
  lcd.iniciar();
  lcd.imprimir("Iniciando...");
  dht.iniciar();
  pinMode(SMS_VCC, OUTPUT);
  pinMode(SMS_GND, OUTPUT); 
  pinMode(SENSOR_UMI_SOLO1, INPUT);
  pinMode(SENSOR_UMI_SOLO2, INPUT);
  pinMode(SENSOR_UMI_SOLO3, INPUT);
  pinMode(PIN_BOMBA, OUTPUT);
  pinMode(PIN_SOLENOIDE1, OUTPUT);
  delay(1000);
}

void loop() {
  // Aqui só implementa a lógica do sistema
  lcd.imprimir("lendo sensores...");
  lerSensores();
  int mediaUmidade = (solo1.getValor() + solo2.getValor() + solo3.getValor()) / 3;
  delay(100);
  if (mediaUmidade < SOLO_SECO) { // SOLO_SECO = 40
    lcd.imprimir("solo seco", 0, 1);
    delay(2000);
    agitarSolucao();
    delay(100);
    lcd.imprimir("liberar solu");
    liberarSolucao();
  }
  else {
    lcd.imprimir("de boas e.e");
    delay(1000);
  }
  delay(50);
}

void liberarSolucao() {
    bomba.desligar();
    solenoide_plantas.ligar();
    lcd.imprimir("liberando sol");
    lcd.imprimir("B: 0 P: 1 C: 0", 0, 1);
    delay(1000);
    int mediaUmidade = 0;
    lcd.imprimir("B: 1 P: 1 C: 0", 0, 1);
    while (mediaUmidade < SOLO_UMIDO) {
      bomba.ligar();
      solo1.ler();
      solo2.ler();
      solo3.ler();
      mediaUmidade = (solo1.getValor() + solo2.getValor() + solo3.getValor()) / 3;
    }
    bomba.desligar();
    solenoide_plantas.desligar();
    lcd.imprimir("Irrigado!");
    lcd.imprimir("B: 0 P: 0 C: 0", 0, 1);
    delay(2000);
}

void agitarSolucao() {
  lcd.imprimir("agitando solu");
  lcd.imprimir("B: 0 P: 0 C: 1", 0, 1);
  delay(1000);
  solenoide_plantas.desligar();
  solenoide_caixa.ligar();
  delay(100);
  bomba.ligar();
  lcd.imprimir("B: 1 P: 0 C: 1", 0, 1);
  delay(1000);
  unsigned long tempo = 0;
  while (tempo != 180) {
    tempo++;
    delay(100);
  }
  bomba.desligar();
  delay(100);
  solenoide_caixa.desligar();
  lcd.imprimir("agitado!");
  lcd.imprimir("B: 0 P: 0 C: 0", 0, 1);
  delay(1000);
}

int lerSensores() {
  int error = 0;
  solo1.ler();
  solo2.ler();
  solo3.ler();
  ldr1.ler();
  error = dht.ler();
  return 0;
}

/*
void calcularTempo() { // Função que calcula tempo que o arduino está ligado (Aconselhasse utilizar direto no loop)
  tempoPassado = millis() - (tempoInicial); // mensurando o tempo
  if (tempoPassado > (tempoAmostra*1000)) {
    tempoInicial = millis();
  }
}
*/

