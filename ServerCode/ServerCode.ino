#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "RTClib.h"
#include "SD.h"
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>








// Wifi Connection
const char* ssid = "100";
const char* password = "mahdihastam";





// Server STATIC IP Address
IPAddress local_IP(192, 168, 1, 254);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");



// Sd Card File Object
File dataFile;








// RTC ( Time )  Tehran UTC
const char* ntpServer = "pool.ntp.org";
const long utcOffsetInSeconds = 12600;  // UTC offset for Tehran



// Wifi For Time Update
WiFiUDP ntpUDP;
RTC_DS3231 rtc;

// Time Client Object
NTPClient timeClient(ntpUDP, ntpServer, utcOffsetInSeconds);
DateTime now;




// SD CART Cheap Select Pin
const int SD_CHIP_SELECT = 5;






TaskHandle_t Task1;

bool ledState = 0;
const int ledPin = 2;
int counter = 0;






// Response Types
const int RESPONSE_TYPE_CONNECTION = 1;
const int RESPONSE_TYPE_GET = 2;
const int RESPONSE_TYPE_PUT = 3;
const int RESPONSE_TYPE_CHANGE = 4;
const int RESPONSE_TYPE_MESSAGE = 5;
const int RESPONSE_TYPE_CHIP_INFO = 6;
const int RESPONSE_TYPE_MPU_FFT = 7;





void setup() {
  Serial.begin(115200);
  initSdCart();
  initWiFi();
  initTime();
  initWebSocket();
  getUpdatedTime();
  initTaksCoreTwo();
  initOTA();
  delay(2000);
}




void Task1code(void* parameter) {
  while (true) {
    DynamicJsonDocument doc(256);
    ws.cleanupClients();
    digitalWrite(ledPin, ledState);
    counter++;
    doc["type"] = 5;
    doc["message"] = " Hello World !" + String(counter);
    String temp;
    serializeJson(doc, temp);
    ws.textAll(temp);
    delay(1000);
  }
}




void loop() {
  ArduinoOTA.handle();
}
