#include "DHT.h"
#include "UbidotsMicroESP8266.h"
#define DHTPIN 8
#define DHTTYPE DHT11

#define TOKEN "BBFF-90a5d6f4a55d22189747812a1262294349d"
#define ssid "itu"
#define pass "tabokmasaya"

DHT dht(DHTPIN,DHT11);
Ubidots client(TOKEN);
unsigned long last = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(20);
  client.wifiConnection(ssid,pass);
}

void loop() {
  if(millis() - last > 10000){
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    last = millis();
    client.add("kelembapan",hum);
    client.add("Temperatur",temp);
    client.sendAll(true);
  }

}
