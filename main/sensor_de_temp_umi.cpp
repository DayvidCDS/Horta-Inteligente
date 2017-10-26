#include <Arduino.h>
#include <DHT.h>

class TempUmi { // Objeto DHT (modificado)
  private:
    DHT *dht;
    float temp;
    float umi;
  public:
    TempUmi(DHT *dht) { // Construtor, Método iniciado quando se cria a variável (Objeto)
      this->dht = dht; // Setando variável com a sua referência
    }
    void iniciar() {
      this->dht->begin();
    }
    int ler(float *temp, float *umi) const { // Variáveis passadas como referência
      // A leitura da temperatura e umidade pode levar 250ms
      float h = this->dht->readHumidity();
      float t = this->dht->readTemperature();
  
      if (isnan(t) || isnan(h)) { // testa se o retorno é valido
        Serial.println("Falha na leitura do DHT");
        return 1;
      } 
      *temp = t;
      *umi = h;
      return 0;
    }
    int ler() {
      // A leitura da temperatura e umidade pode levar 250ms
      float h = this->dht->readHumidity();
      float t = this->dht->readTemperature();
  
      if (isnan(t) || isnan(h)) { // testa se o retorno é valido
        Serial.println("Falha na leitura do DHT");
        return 1;
      } 
      this->temp = t;
      this->umi = h;
      return 0;
    }
    float getTemp() {
      return this->temp;
    }
    float getUmi() {
      return this->umi;
    }
};
