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

const int read = A3; //Sensor A3 pin to Arduino pin A0
int value;          //Variable to store the incomming data

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
  value = analogRead(A3); //Read data from analog pin and store it to value variable
  if (value<=480){ 
    Serial.println("Water level: 0mm - Empty!"); 
  }
  else if (value>480 && value<=530){ 
    Serial.println("Water level: 0mm to 5mm"); 
  }
  else if (value>530 && value<=615){ 
    Serial.println("Water level: 5mm to 10mm"); 
  }
  else if (value>615 && value<=660){ 
    Serial.println("Water level: 10mm to 15mm"); 
  } 
  else if (value>660 && value<=680){ 
    Serial.println("Water level: 15mm to 20mm"); 
  }
  else if (value>680 && value<=690){ 
    Serial.println("Water level: 20mm to 25mm"); 
  }
  else if (value>690 && value<=700){ 
    Serial.println("Water level: 25mm to 30mm"); 
  }
  else if (value>700 && value<=705){ 
    Serial.println("Water level: 30mm to 35mm"); 
  }
  else if (value>705){ 
    Serial.println("Water level: 35mm to 40mm"); 
  }
}
