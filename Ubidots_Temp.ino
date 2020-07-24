#include "DHT.h"
#include "UbidotsMicroESP8266.h"
#define DHTPIN 5//pin sensor DHT

#define TOKEN "BBFF-LkpDJzsO4he4W58SWFAJrmGrCz9UjZ"  
#define ssid "12345678"
#define pswd "123456789"

 DHT dht(DHTPIN,DHT11);
 Ubidots client(TOKEN);
 unsigned long last =0;

void setup() {

  Serial.begin(9600);
  dht.begin();
  delay(20);
  client.wifiConnection(ssid,pswd);  // klau ssid memakai pass
 
  //  client.wifiConnection(ssid,NULL); // klau ssid tdk memakai pass
}

void loop() {

  if(millis()-last>1000){
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();
    last=millis();
    client.add("Humidity",hum);
    client.add("Temperature",temp);
    client.sendAll(true);

  }
}
