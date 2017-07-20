#include "DHT.h"

#define DHTPIN 2     // Digitalni pin koji se koristi
#define DHTTYPE DHT22   // tip DHT-a DHT22

int maxHum = 60;
int maxTemp = 20;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  dht.begin();
}

void loop() {
  // 2sek pauza
  delay(2000);

  // citanje traje 250ms!
  float h = dht.readHumidity();
  // citanje temperature u C
  float t = dht.readTemperature();
  
  
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");

}
