#include "MoistureSensor.h"


int n_leituras = 10;
int s_umidade = A0;
int rele = 5;
int threshold = 900;

MoistureSensor ms(s_umidade, n_leituras);

const int DELAY = 30 * 100;

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
  delay(2000);
  for (int i = 0; i < n_leituras ; i++) {
    ms.reset();
    ms.read();
    delay(1);
  }

  int leitura = ms.getSmoothedReading();
  Serial.println(leitura);
  delay(DELAY);
}
