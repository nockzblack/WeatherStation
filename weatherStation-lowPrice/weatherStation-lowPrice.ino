//  LIBRARIES
#include <OneWire.h> // DS18B20 temp sensor            
#include <DallasTemperature.h> // DS18B20 temp sensor 

#include "DHT.h" // DTH11 ambiental humidty sensor  

OneWire auxWire(3); // temp sentor to pin 3 on Arduino
DallasTemperature tempSensor(&auxWire);

DHT dht(4, DHT11); // ambiental humidty sentor to pin 4 on Arduino

void setup() {
  
  Serial.begin(9600); // Initializing serial comunication
  
  tempSensor.begin(); // Initializing temperature sensor (DS18B20)
  dht.begin(); // Initializing ambiental humidity sensor (DTH11)
}

void loop() {
  float currentTemp = getTemp();
  float currentAmbientalHumidity = getAmbientalHumidity();

}

float getAmbientalHumidity() {
  float ambientalHumidty = dht.readHumidity();
  if (isnan(ambientalHumidty)) {
    Serial.println("Falla al leer el sensor DHT11!");
    return 0;
  }

  return ambientalHumidty;
}

float getTemp() {
  tempSensor.requestTemperatures();
  float temp = tempSensor.getTempCByIndex(0);
  return temp;
}

