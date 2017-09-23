#include "MoistureSensor.h"
#include <ESP8266WiFi.h>
#include <aREST.h>

aREST rest = aREST();

const char* ssid = "Torre Stark";
const char* password = "abacate15";

#define LISTEN_PORT           80

WiFiServer server(LISTEN_PORT);


int n_leituras = 10;
int s_umidade = A0;
int rele = 5;
int threshold = 900;
int leitura;

MoistureSensor ms(s_umidade, n_leituras);

const int DELAY = 30 * 100;

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);

  rest.set_id("1");
  rest.set_name("noise_esp8266");
  leitura = 0;
  rest.variable("leitura",&leitura);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connectado");

  // Inicia o servidor
  server.begin();
  Serial.println("Servidor iniciado");

  // Exibe o IP na rede
  Serial.println(WiFi.localIP());
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

  if (leitura > threshold) {
    digitalWrite(rele, LOW);
  } else {
    digitalWrite(rele, HIGH);
  }
  
  digitalWrite(13, LOW);
  delay(DELAY);
}
