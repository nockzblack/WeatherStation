/**
   GeekFactory - "Construye tu propia tecnologia"
   Distribucion de materiales para el desarrollo e innovacion tecnologica
   www.geekfactory.mx
 
   EJEMPLO SENSOR DHT11 1
 
   EJEMPLO PARA EL SENSOR DHT11 QUE PERMITE MEDIR HUMEDAD Y TEMPERATURA. ESTE SENSOR
   ES MUY ECONÓMICO Y PODEMOS USARLO PARA DETECTAR LA HUMEDAD EN EL AMBIENTE EN ZONAS
   COMO INVERNADEROS, LAVANDERIAS, FABRICAS Y BAÑOS. USAMOS LA LIBRERIA DHT DE ADAFRUIT
   PARA COMUNICARSE CON EL DHT11 Y DHT22

   https://www.luisllamas.es/arduino-dht11-dht22/
 
*/
#include "DHT.h"
 
// CONSTRUCTOR DEL OBJETO DHT RECIBE EL PIN EN EL QUE SE CONECTA EL SENSOR
// Y TAMBIEN RECIBE EL TIPO DE SENSOR QUE VAMOS A CONECTAR
DHT dht(3, DHT11);
 
void setup() {
  // PREPARAR LA COMUNICACION SERIAL
  Serial.begin(9600);
  Serial.println("Prueba del sensor DHT11");
  
  // PREPARAR LA LIBRERIA PARA COMUNICARSE CON EL SENSOR
  dht.begin();
}
 
void loop() {
  // ESPERAR ENTRE MEDICIONES, NECESARIO PARA EL BUEN FUNCIONAMIENTO
  delay(2000);
  
  // LEER LA HUMEDAD USANDO EL METRODO READHUMIDITY
  float h = dht.readHumidity();
  // LEER LA TEMPERATURA USANDO EL METRODO READTEMPERATURE
  float t = dht.readTemperature();
 
  // REVISAR QUE LOS RESULTADOS SEAN VALORES NUMERICOS VALIDOS, INDICANDO QUE LA COMUNICACION ES CORRECTA
  if (isnan(h) || isnan(t)) {
    Serial.println("Falla al leer el sensor DHT11!");
    return;
  }
 
  // IMPRIMIR RESULTADO AL MONITOR SERIAL
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");
}
