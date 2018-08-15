#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <DNSServer.h>           
#include <ESP8266WebServer.h>    
#include <WiFiManager.h> 

#include <FastLED.h>

#define LED_PIN     1
#define NUM_LEDS    7
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

unsigned int localPort = 2390; 

IPAddress timeServerIP;
const char* ntpServerName = "time.nist.gov";

const int NTP_PACKET_SIZE = 48; 
byte packetBuffer[ NTP_PACKET_SIZE];

WiFiUDP udp;
CRGB leds[NUM_LEDS];
CRGB color = CRGB::Green;

void setupWifiConfigurationPortal(){
  WiFiManager wifiManager;

  wifiManager.setAPCallback(configModeCallback);

  if(!wifiManager.autoConnect("Tick Tock Clock")){
    Serial.println("Failed to connect to wifi, trying again in 1 second");
    ESP.reset();
    delay(1000);
  }
}

void configModeCallback(WiFiManager *wifiManager) {
  Serial.println("Entered config mode: ");
  Serial.println(WiFi.softAPIP());
  Serial.println(wifiManager->getConfigPortalSSID());
}

void setupWifiForUdpPackets(){
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  udp.begin(localPort);
}

void setupLed() {
  delay(3000); //Power up safety delay for the WS2811
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void setup() {
  Serial.begin(115200);

  setupLed();
  setupWifiConfigurationPortal();
  setupWifiForUdpPackets();
}

void loop() {
  WiFi.hostByName(ntpServerName, timeServerIP); //get a random server from the pool
  sendNTPpacket(timeServerIP); // request the time
  delay(1000); // wait 1 seconds to check if we received the time

  int cb = udp.parsePacket();
  if (cb) {
    receiveTime(cb);
  } else {
    Serial.println("no packet yet");
  }
  
  // wait ten seconds before asking for the time again
  delay(10000);
}

void receiveTime(int cb) {
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    
    const unsigned long seventyYears = 2208988800UL;
    unsigned long epoch = secsSince1900 - seventyYears;
    
    Serial.println(epoch);

    int hour = (epoch  % 86400L) / 3600;
    int minutes = (epoch % 3600) / 60;

    showNumber(minutes%10);
    
    Serial.print(hour);
    Serial.print(":");
    Serial.println(minutes%10); // print the second
}

void sendNTPpacket(IPAddress& address) {
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

void showNumber(int number){
  switch (number) {
  case 0:
    showNumberZero(0,color);
    break;
  case 1:
    showNumberOne(0,color);
    break;
  case 2:
    showNumberTwo(0,color);
    break;
  case 3:
    showNumberThree(0,color);
    break;
  case 4:
    showNumberFour(0,color);
    break;
  case 5:
    showNumberFive(0,color);
    break;
  case 6:
    showNumberSix(0,color);
    break;
  case 7:
    showNumberSeven(0,color);
    break;
  case 8:
    showNumberEight(0,color);
    break;
  case 9:
    showNumberNine(0,color);
    break;
  }
  
  FastLED.show();
}

void showNumberZero(int startLed,CRGB color){
  leds[0] = color;
  leds[1] = color;
  leds[2] = color;
  leds[3] = CRGB::Black;
  leds[4] = color;
  leds[5] = color;
  leds[6] = color;
}

void showNumberOne(int startLed,CRGB color){
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  leds[2] = color;
  leds[3] = CRGB::Black;
  leds[4] = CRGB::Black;
  leds[5] = CRGB::Black;
  leds[6] = color;
}

void showNumberTwo(int startLed,CRGB color){
  leds[0] = color;
  leds[1] = color;
  leds[2] = CRGB::Black;
  leds[3] = color;
  leds[4] = CRGB::Black;
  leds[5] = color;
  leds[6] = color;
}

void showNumberThree(int startLed,CRGB color){
  leds[0] = CRGB::Black;
  leds[1] = color;
  leds[2] = color;
  leds[3] = color;
  leds[4] = CRGB::Black;
  leds[5] = color;
  leds[6] = color;
}

void showNumberFour(int startLed,CRGB color){
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  leds[2] = color;
  leds[3] = color;
  leds[4] = color;
  leds[5] = CRGB::Black;
  leds[6] = color;
}

void showNumberFive(int startLed,CRGB color){
  leds[0] = CRGB::Black;
  leds[1] = color;
  leds[2] = color;
  leds[3] = color;
  leds[4] = color;
  leds[5] = color;
  leds[6] = CRGB::Black;
}

void showNumberSix(int startLed,CRGB color){
  leds[0] = color;
  leds[1] = color;
  leds[2] = color;
  leds[3] = color;
  leds[4] = color;
  leds[5] = color;
  leds[6] = CRGB::Black;
}

void showNumberSeven(int startLed,CRGB color){
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  leds[2] = color;
  leds[3] = CRGB::Black;
  leds[4] = CRGB::Black;
  leds[5] = color;
  leds[6] = color;
}

void showNumberEight(int startLed,CRGB color){
  leds[0] = color;
  leds[1] = color;
  leds[2] = color;
  leds[3] = color;
  leds[4] = color;
  leds[5] = color;
  leds[6] = color;
}

void showNumberNine(int startLed,CRGB color){
  leds[0] = CRGB::Black;
  leds[1] = color;
  leds[2] = color;
  leds[3] = color;
  leds[4] = color;
  leds[5] = color;
  leds[6] = color;
}


