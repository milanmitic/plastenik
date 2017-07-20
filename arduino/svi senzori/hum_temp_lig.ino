/*
 
Example of BH1750 library usage.
 
This example initalises the BH1750 object using the default
high resolution mode and then makes a light level reading every second.
https://github.com/claws/BH1750 library za senzor 
Connection:
 VCC-5v
 GND-GND
 SCL-SCL(analog pin 5)
 SDA-SDA(analog pin 4)
 ADD-NC or GND
 
*/
 
#include <Wire.h>
#include <BH1750.h>
#include "DHT.h"

#define DHTPIN 2     // Digitalni pin koji se koristi
#define DHTTYPE DHT22   // tip DHT-a DHT22

int maxHum = 60;
int maxTemp = 20;

int sensor_pin = A0; 
int output_value ;

DHT dht(DHTPIN, DHTTYPE); 
 
BH1750 lightMeter;
 
 
void setup(){
  Serial.begin(9600);
  lightMeter.begin();
  Serial.println("Running...");
  dht.begin();
}
 
 
void loop() {
  // 2sek pauza
  delay(2000);
  uint16_t lux = lightMeter.readLightLevel();
  // citanje traje 250ms!
  float h = dht.readHumidity();
  // citanje temperature u C
  float t = dht.readTemperature();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");
  output_value= analogRead(sensor_pin);
  output_value = map(output_value,550,0,0,100);
  Serial.print("Moisture : ");
  Serial.print(output_value);
  Serial.println("%");
}
