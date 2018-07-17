//  LIBRARIES
#include <OneWire.h> // DS18B20 temp sensor            
#include <DallasTemperature.h> // DS18B20 temp sensor 
#include <DHT.h> // DTH11 ambiental humidty sensor 
#include <EtherCard.h>



/*
 *  Digital Temp Sensor DS18B20
 *  
 *  Temp Range: -55 to 125°C
 *  Power: 3.0 V to 5.5 V
 *  Accuracy: ±0.5°C (from -10°C to +85°C)
 *  
 */
OneWire auxWire(3); // declaring temp sensor to pin 3 on Arduino
DallasTemperature tempSensor(&auxWire);



/*
 *  Humidity Sensor DHT11
 *  Power: 3 y 5 volts
 *  Good for 20-80% humidity readings with 5% accuracy
 */
DHT dht(4, DHT11); // declaring ambiental humidity sentor to pin 4 on Arduino



/*
 *  Air Quality Sensor MQ135
 *  Measure NH3, NOx, alcohol, Benzene, smoke, CO2
 *  Range of values Values:
 *    normal outdoor level: 350 - 450 ppm
 *    acceptable levels: < 600 ppm
 */
const int airQuality = A1; // declaring air Quiality  sensor to analog input A1 on arduino


/*
 *  Ground Humidity Sensor FC-28
 *  The range of values from 0 submerged in water to 1023 in the air.
 *  A slightly humid ground would give typical values of 600-700.
 *  A dry ground gives values between 800-1023.
 */

const int groundHumidity = A0; // declaring ground humidity sensor to analog input A0



// ENCJ2860  -> Arduino
// SCK       ->  pin 13 
// SO        ->  pin 12
// SI        ->  pin 11
// CS        ->  pin 10
// VCC       ->  3V3 
// GND       -> GND

// Decalaring Ethernet values nedeed
static byte macAddress[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 }; // ethernet interface mac address, must be unique on the LAN
byte Ethernet::buffer[500]; 
BufferFiller auxBuffer;   //This object populates network send and receive buffers.
#define STATIC 1 //  DHCP=0 ,  static=1
#if STATIC  
  static byte IPAdress[] = { 192,168,1,200 }; // static ip address
#endif





unsigned long milisSec = 0;
float currentTemp = 0;
float currentAmbientalHumidity = 0;
int currentGroundHumidity = 0;
int currentAirQuality = 0;

void setup() {
  
  Serial.begin(9600); // Initializing serial comunication
  Serial.println("Serial comunication initialized");
  tempSensor.begin(); // Initializing temperature sensor (DS18B20)
  dht.begin(); // Initializing ambiental humidity sensor (DTH11)
  pinMode(groundHumidity, INPUT); // Initializing ground humidity sensor
  pinMode(airQuality, INPUT); // Initializing air Quality  sensor

  
  
  // Initializing Ethernet values
  // Mac Addresse
  if (ether.begin(sizeof Ethernet::buffer, macAddress, 10) == 0) {
    Serial.println( "Failed to access Ethernet controller");
  }
  


  #if STATIC 
    ether.staticSetup(IPAdress);
  #else
    Serial.println("Waiting for DHCP");
    if (!ether.dhcpSetup()) {
      Serial.println("DHCP failed");
    }else {
      Serial.println("DHCP working");
    }
  #endif
    ether.printIp("IP:  ", ether.myip);

 

  milisSec = 0;
  
  currentTemp = getTemp();
  currentAmbientalHumidity = getAmbientalHumidity();
  currentGroundHumidity = getGroundHumidity();
  currentAirQuality = getAirQuality();
  
  
  Serial.println("\nSetup Finished\n");

}



void loop() {

  
  if (milisSec == 1000) { // 3 minutes to read the data from the enviroment 180000
    currentTemp = getTemp();
    currentAmbientalHumidity = getAmbientalHumidity();
    currentGroundHumidity = getGroundHumidity();
    currentAirQuality = getAirQuality();
    milisSec = 0;

    Serial.print("Temp: ");
    Serial.print(currentTemp);
    Serial.println(" ªC");
    
    Serial.print("Air Humidity: ");
    Serial.println(currentAmbientalHumidity);
    
    Serial.print("Ground Humidity: ");
    Serial.println(getGroundHumidity());
    Serial.print("Air Quality: ");
    Serial.println(currentAirQuality);
    Serial.println("------------ \n \n");
    
  }
  

  
  
  word len = ether.packetReceive(); // polls for new incoming data and copies it into the global buffer. The return value is the size of this packet
  
  word pos = ether.packetLoop(len); // looks at the incoming data and takes care of low-level responses
  // The return value is the offset in the global packet buffer where incoming TCP data can be found (or zero if there is none)
  
  if (pos) { // if valid tcp data received send web page
      ether.httpServerReply(htmlPage(currentTemp,currentAirQuality, currentAmbientalHumidity, currentGroundHumidity)); // Send a respons to a HTTP request.
    }


  milisSec++;
  
  
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


static word htmlPage(float temp, int airQuality, float airHumidity, int groundHumidity) {

  // Format temp : +00.00
  // Decimals for temp
  int decimalsToLeftTemp = temp*100;
  long longTemp = temp;
  long decimalsTemp = decimalsToLeftTemp%100;

  
  long longAirQuality = airQuality;
  long longGroundHumidity = groundHumidity;

  // Format air humidity : 00.00
  // Decimals for air humidity
  int decimalsToLeftAir = airHumidity*100;
  long longAirHumidity = airHumidity;
  long decimalsAirHumidity = decimalsToLeftAir%100;
  

  auxBuffer = ether.tcpOffset(); // Pointer to the start of TCP payload. 

  // Add formatted text to buffer, the first parameter is a fmt format string and the the others are parameters for format string
  auxBuffer.emit_p(
    PSTR( 
        "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"
        // Starts HTML CODE
        "<meta http-equiv='refresh' content='1'/>"
        "<body><html>"
        "<h1>Whether Station</h1>"
        "<h3>Temp: $L.$L C </h3>"
        "<h3>Calidad del Aire: $L ppm </h3>"
        "<h3>Humedad del Suelo: $L </h3>"
        "<h3>Humedad del Ambiemte: $L.$L %</h3>"
        "</body></html>"
    ), longTemp, decimalsTemp, longAirQuality, longGroundHumidity, longAirHumidity, decimalsAirHumidity);

  delay(10);
  return auxBuffer.position();
}


