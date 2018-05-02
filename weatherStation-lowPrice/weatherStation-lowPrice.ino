//  LIBRARIES
#include <OneWire.h> // DS18B20 temp sensor            
#include <DallasTemperature.h> // DS18B20 temp sensor 
#include <DHT.h> // DTH11 ambiental humidty sensor 
#include <EtherCard.h>

OneWire auxWire(3); // declaring temp sensor to pin 3 on Arduino
DallasTemperature tempSensor(&auxWire);

DHT dht(4, DHT11); // declaring ambiental humidity sentor to pin 4 on Arduino
const int groundHumidity = A0; // declaring ground humidity sensor to analog input A0
const int airQuality = A1; // declaring air Quiality  sensor to analog input A1 on arduino


// Decalaring Ethernet values nedeed
static byte macAdress[] = { 0x74,0x69,0x69,0x2D,0x30,0x33 }; // ethernet interface mac address, must be unique on the LAN
byte Ethernet::buffer[500]; 
BufferFiller auxBuffer;   //This object populates network send and receive buffers.
#define STATIC 0  //  DHCP=0 ,  static=1
#if STATIC  
static byte IPAdress[] = { 192,168,1,200 }; // static ip address
#endif

// ENCJ2860  -> Arduino
// SCK       ->  pin 13 
// SO        ->  pin 12
// SI        ->  pin 11
// CS        ->  pin 10
// VCC       ->  3V3 
// GND       -> GND


unsigned long milisSec = 0;
long currentTemp = 0;
long currentAmbientalHumidity = 0;
int currentGroundHumidity = 0;
int currentAirQuality = 0;

void setup() {
  
  Serial.begin(9600); // Initializing serial comunication
  tempSensor.begin(); // Initializing temperature sensor (DS18B20)
  dht.begin(); // Initializing ambiental humidity sensor (DTH11)
  pinMode(groundHumidity, INPUT); // Initializing ground humidity sensor
  pinMode(airQuality, INPUT); // Initializing air Quality  sensor
  
  // Initializing Ethernet values
  // Mac Address
  if (ether.begin(sizeof Ethernet::buffer, macAdress) == 0) {
    Serial.println( "Failed to access Ethernet controller");
  }

  #if STATIC 
    ether.staticSetup(IPAdress);
  #else
    if (!ether.dhcpSetup()) 
      Serial.println("DHCP failed");
  #endif
    ether.printIp("IP:  ", ether.myip);

  milisSec = 0;
  currentTemp = getTemp();
  currentAmbientalHumidity = dht.readHumidity();
  currentGroundHumidity = getGroundHumidity();
  currentAirQuality = getAirQuality();

}



void loop() {
  
  if (milisSec == 180000) {
    currentTemp = getTemp();
    currentAmbientalHumidity = dht.readHumidity();
    currentGroundHumidity = getGroundHumidity();
    currentAirQuality = getAirQuality();
    milisSec = 0;
  }
  

  

  word len = ether.packetReceive(); // polls for new incoming data and copies it into the global buffer. The return value is the size of this packet
  
  word pos = ether.packetLoop(len); // looks at the incoming data and takes care of low-level responses
  // The return value is the offset in the global packet buffer where incoming TCP data can be found (or zero if there is none)
  
  if (pos) { // if valid tcp data received send web page
      ether.httpServerReply(htmlPage(currentTemp,currentAirQuality, currentAmbientalHumidity, currentGroundHumidity)); // Send a respons to a HTTP request.
    }

  //delay(100);
  /*
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
  Serial.println("\n");
  Serial.println("\n");
  Serial.println("\n");
  */

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

long getTemp() {
  tempSensor.requestTemperatures();
  long temp = tempSensor.getTempCByIndex(0);
  return temp;
}


static word htmlPage(long temp, long airQuality, long airHumidity, long groundHumidity) {
  /*
  long temp = 28.0;
  long airQuality = 45;
  long ligthIntensity = 1344;
  long airHumidity = 20;
  long groundHumidity = 50;
  */

  auxBuffer = ether.tcpOffset(); // Pointer to the start of TCP payload. 

  // Add formatted text to buffer, the first parameter is a fmt format string and the the others are parameters for format string
  auxBuffer.emit_p(
    PSTR( 
        "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"
        // Starts HTML CODE
        "<meta http-equiv='refresh' content='1'/>"
        "<body><html>"
        "<h1>Whether Station</h1>"
        "<h3>Temperatura: $LºC </h3>"
        "<h3>Calidad del Aire: $L ppm </h3>"
        "<h3>Humedad del Suelo: $L %</h3>"
        "<h3>Humedad del Ambiemte: $L %</h3>"
        "</body></html>"
    ), temp, airQuality, groundHumidity, airHumidity);

  delay(10);
  return auxBuffer.position();
}


