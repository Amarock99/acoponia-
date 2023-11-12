// Bibliotecas
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "DHT.h"
#include <AceTime.h>

// Definições
// Define o tipo de sensor 
#define DHTTYPE DHT22 

// Configuração do pino do sensor DHT22
#define DHTPIN 12

// Configuração do pino do OLED 
#define OLED_RESET 4

// Configuração do display
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  // I2C
  Wire.begin();

  dht.begin();

  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
  display.clearDisplay(); 
}

void loop() {
  // Como o DHT precisa de um tempo, aqui damos a ele
  delay(2000);

  // Coletando os inputs DHT22
  float h = dht.readHumidity(); // Umidade
  float t = dht.readTemperature(); // Temperatura Celsius
  float f = dht.readTemperature(true); // Temperatura Fahrenheit

  // Teste para saber se o sensor está funcionando corretamente 
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Calcula a temperatura em graus Celsius
  float hic = dht.computeHeatIndex(t, h, false);

  // Usado para converter o sinal analógico como vimos logo abaixo 
  const float BETA = 3950;
  int analogValue = analogRead(A0);

  // Variável que armazena a temperatura 
  float celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;

  // Ligar de verdade o LED
  display.setTextColor(WHITE);
  
  // Tamanho da fonte
  display.setTextSize(1);

  // Define a posição do cursor no x, y
  // Teste de prints hihihi
  display.setCursor(0, 0);
  display.print("Temp Agua: ");
  display.setCursor(60, 0);
  display.print(celsius);
  display.setCursor(0, 10);
  display.print("umidade: ");
  display.print(h);
  display.print("%");
  display.setCursor(0, 20);
  display.print("Temperatura: ");
  display.print(t);

  display.display();
}
