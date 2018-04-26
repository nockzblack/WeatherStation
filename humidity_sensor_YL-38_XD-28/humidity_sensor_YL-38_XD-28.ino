/*
* The module YL-38 has a digital and an anlog output.
* The digtal input 0/1 is setted using the potentiometer included
* in the module YL-38.
* With the analog signal the range of values are from 0-1023
* Very wet land: 0-350
* wet land: 351-600
* dry land: 601-1023
* 
* For mor info:
* https://myrobotself.com/2016/07/23/sensor-de-humedad-del-suelo-modulos-yl-69-y-yl-38/
*/

const int analogPin = A3;
const int digitalPin = 2;
 
void setup() {
   Serial.begin(9600);
   pinMode(digitalPin, INPUT);
}
 
void loop() 
{
   int analogHumididty = analogRead(analogPin);
   int digitalHumidity = digitalRead(digitalPin);
   
   Serial.print("Analog Input: ");
   Serial.println(analogHumididty);
   Serial.print("Digital Input: ");
   Serial.println(digitalHumidity);
   delay(1000);
}


 

