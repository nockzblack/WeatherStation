//  LIBRARIES
#include <OneWire.h> // DS18B20 temp sensor            
#include <DallasTemperature.h> // DS18B20 temp sensor 

#include <DHT.h> // DTH11 ambiental humidty sensor  

OneWire auxWire(3); // declaring temp sensor to pin 3 on Arduino
DallasTemperature tempSensor(&auxWire);

DHT dht(4, DHT11); // declaring ambiental humidity sentor to pin 4 on Arduino
const int groundHumidity = A0; // declaring ground humidity sensor to analog input A0
const int airQuality = A1; // declaring air Quiality  sensor to analog input A1 on arduino


void setup() {
  
  Serial.begin(9600); // Initializing serial comunication
  
  tempSensor.begin(); // Initializing temperature sensor (DS18B20)
  dht.begin(); // Initializing ambiental humidity sensor (DTH11)
  pinMode(groundHumidity, INPUT); // Initializing ground humidity sensor
   pinMode(airQuality, INPUT); // Initializing air Quality  sensor
}

void loop() {
  float currentTemp = getTemp();
  float currentAmbientalHumidity = getAmbientalHumidity();
  int currentGroundHumidity = getGroundHumidity();
  int currentAirQuality = getAirQuality();

  Serial.print("Temp = ");
  Serial.print(currentTemp);
  Serial.println("ºC");
  
  Serial.print("Ambiental Humidity = ");
  Serial.print(currentAmbientalHumidity);
  Serial.println("%");
  
  Serial.print("Ground Humidity = ");
  Serial.print(currentGroundHumidity);
  Serial.println("Escala desconocina");
  
  Serial.print("Air Quality = ");
  Serial.print(currentAirQuality);
  Serial.println("*Particulas por Millon");

  delay(500);
}

int getAirQuality() {
  return analogRead(airQuality);
}

int getGroundHumidity() {
  return analogRead(groundHumidity);
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

