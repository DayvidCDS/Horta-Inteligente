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
#define NOITE 30

#define SOLO_SECO 40
#define SOLO_UMIDO 60

// Instanciando objetos

Rele bomba1(PIN_BOMBA, NIVEL_LOGICO_RELE_BOMBA); // Instanciando o rele da bomba
// Rele solenoide1();

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
void liberar(Solo *, Ldr *, Rele *);
void lerSensores(Solo *, Ldr *, TempUmi *);
void agitarSolucao();

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

  if (lerSensores()) {
    liberar();
  }
  else {
    lcd.apagarTudo();
    lcd.imprimir("Falha na leitura", 0, 0);
    lcd.imprimir("dos sensores", 0, 1);
  }
  
}

void liberar(Solo *solo, Ldr *luz, Rele *bomba) {
  if (solo->ler() <= SOLO_SECO && luz->getLuz() <= NOITE) {
    unsigned char umiSolo = SOLO_SECO;
    while (umiSolo < SOLO_UMIDO) { // Treta das solenoides
      bomba->ligar(); 
      umiSolo = solo->ler();
      delay(100);
    }
    bomba->desligar();
  }
}

void agitarSolucao() {
  // treta com as solenoides
}

void lerSensores(Solo *solo, Ldr *ldr, TempUmi *dht) {
  int error = 0;
  solo->ler();
  ldr->ler();
  error = dht->ler();
  if (solo->getValor() == 0 || solo->getValor == 1 || ldr->getValor() == 0 || ldr->getValor() == 1 || error == 1) {
    return 1;
  }
  return 0;
}

void calcularTempo(unsigned long *tempoPassado, unsigned long *tempoInicial, unsigned const long tempoAmostra) { // Função que calcula tempo que o arduino está ligado (Aconselhasse utilizar direto no loop)
  *tempoPassado = millis() - (*tempoInicial); // mensurando o tempo
  if (*tempoPassado > (tempoAmostra*1000)) {
    *tempoInicial = millis();
  }
}

