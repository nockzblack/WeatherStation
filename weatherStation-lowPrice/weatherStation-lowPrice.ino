//  LIBRARIES
#include <OneWire.h>                
#include <DallasTemperature.h>

OneWire auxWire(3); // pin 3 on Arduino
DallasTemperature tempSensor(&auxWire);

void setup() {
  
  Serial.begin(9600); // Initializing serial comunication
  
  tempSensor.begin(); // Initializing temperature sensor (DS18B20)

}

void loop() {
  float ambientalTemp = getTemp();

}

float getTemp() {
  tempSensor.requestTemperatures();
  float temp = tempSensor.getTempCByIndex(0);
  return temp;
}

