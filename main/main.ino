#include "MoistureSensor.h"

int n_leituras = 10;
int s_umidade = A0;
int rele = 8;

//  limite para ativar a irrigacao
int threshold = 900;

MoistureSensor ms(s_umidade, n_leituras);

const int DELAY = 30 * 100;

/*
 * TODO:
 *    - Calcular o valor correto de acordo com a formula
 *    - Pegar os dados de clima com ESP
 *    - Verificar se o reservatorio precisar ser cheio ou nao
 */

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(rele, OUTPUT);
}

void loop() {

  digitalWrite(13, HIGH);

  // tempo para o sensor estabilizar
  delay(2000);
  
  for (int i = 0; i < n_leituras; i++) {
    ms.reset();
    ms.read();
    delay(1);
  }

  int leitura = ms.getSmoothedReading();
  Serial.println(leitura);

  if (leitura > threshold) {
    digitalWrite(rele, LOW);
  } else {
    digitalWrite(rele, HIGH);
  }
  
  digitalWrite(13, LOW);
  delay(DELAY);
}
