// Arduino Webserver with module Ethernet  ENC28J60
// Webpage shows data for a Weather Station
// Code adopted by Fernando Benavides @Nockzblack 2018.04.29

// ENCJ2860  -> Arduino
// SCK       ->  pin 13 
// SO        ->  pin 12
// SI        ->  pin 11
// CS        ->  pin 10
// VCC       ->  3V3 
// GND       -> GND

#include <EtherCard.h>


// Decalaring Ethernet values nedeed
static byte macAdress[] = { 0x74,0x69,0x69,0x2D,0x30,0x33 }; // ethernet interface mac address, must be unique on the LAN

byte Ethernet::buffer[500]; 

BufferFiller auxBuffer;   //This object populates network send and receive buffers.

static byte IPAdress[] = { 192,168,1,200 }; // static ip address


#define STATIC 0  //  DHCP=0 ,  static=1
#if STATIC  
static byte myip[] = { 192,168,1,200 }; // static ip address
#endif




float t1 = 100; // temperature 
int button=3; long state=0; long clicks=0; // for the digital input button
long AIN;

void setup(){ 
  Serial.begin(9600);
  Serial.println("Arduino Webserver with ENC28J60 Ethernet");
  Serial.println ("Low Cost Wheter Station");

  // Initializing Ethernet values
  // Mac Address
  if (ether.begin(sizeof Ethernet::buffer, macAdress) == 0) {
    Serial.println( "Failed to access Ethernet controller");
  }
  /*
  // IP Adress
  ether.staticSetup(IPAdress);
  ether.printIp("IP:  ", ether.myip);
  */

#if STATIC 
   ether.staticSetup(myip);
#else
  if (!ether.dhcpSetup()) 
     Serial.println("DHCP failed");
#endif
  ether.printIp("IP:  ", ether.myip);
  
}


static word htmlPage() {

  long temp = 28.0;
  long airQuality = 45;
  long ligthIntensity = 1344;
  long airHumidity = 20;
  long groundHumidity = 50;

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
        "<h3>Calidad del Aire: $L puntos imeca </h3>"
        "<h3>Intensida de Luz: $L luxes</h3>"
        "<h3>Humedad del Suelo: $L %</h3>"
        "<h3>Humedad del Ambiemte: $L %</h3>"
        "</body></html>"
    ), temp, airQuality, ligthIntensity, airHumidity, groundHumidity);

  return auxBuffer.position();
  
}


void loop () {
  delay(100);
 
  word len = ether.packetReceive(); // polls for new incoming data and copies it into the global buffer. The return value is the size of this packet
  
  word pos = ether.packetLoop(len); // looks at the incoming data and takes care of low-level responses
  // The return value is the offset in the global packet buffer where incoming TCP data can be found (or zero if there is none)
  
  if (pos) { // if valid tcp data received send web page
    
      ether.httpServerReply(htmlPage()); // Send a respons to a HTTP request.
    }
}





