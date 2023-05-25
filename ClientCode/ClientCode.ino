#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <FastLED.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "RTClib.h"
#include <arduinoFFT.h>
#include "SD.h"
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WebSocketsClient.h>


// Sd Cart
#include "SD.h"


// I2C Wires #1
#define SDA_1 21
#define SCL_1 22



// I2C Wires #2
#define SDA_2 33
#define SCL_2 32


// Sd Card File Object
File dataFile;



// Sensors
Adafruit_MPU6050 mpu, mpu2, mpu3, mpu4;


// I2C Wires Objects
TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);


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




WiFiMulti WiFiMulti;
WebSocketsClient webSocket;


const long MPU_TIME_DELAY = 0;
const long TIME_UPDATE_DELAY = 0;


// FFT CONSTS
#define SAMPLES 32         // Must be a power of 2
#define SAMPLING_FREQ 300  // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.





// FFT Values
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned int sampling_period_us;

// FFT Object
arduinoFFT FFT = arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQ);


// FFT Results Values
float frequency = 0;
float frequencyValue = 0;


// Sensor Object
class SensorFFT {
public:
  float get_AX() const {
    return AX;
  }

  void set_AX(float new_AX) {
    AX = new_AX;
  }

  float get_AY() const {
    return AY;
  }

  void set_AY(float new_AY) {
    AY = new_AY;
  }

  float get_AZ() const {
    return AZ;
  }

  void set_AZ(float new_AZ) {
    AZ = new_AZ;
  }

  float get_GX() const {
    return GX;
  }

  void set_GX(float new_GX) {
    GX = new_GX;
  }

  float get_GY() const {
    return GY;
  }

  void set_GY(float new_GY) {
    GY = new_GY;
  }

  float get_GZ() const {
    return GZ;
  }

  void set_GZ(float new_GZ) {
    GZ = new_GZ;
  }

private:
  float AX = 0;
  float AY = 0;
  float AZ = 0;
  float GX = 0;
  float GY = 0;
  float GZ = 0;
};




// Sensors Instances
SensorFFT sensorOneFFT;
SensorFFT sensorTwoFFT;
SensorFFT sensorThreeFFT;
SensorFFT sensorFourFFT;

bool sensorOneActive = false;
bool sensorTwoActive = false;
bool sensorThreeActive = false;
bool sensorFourActive = false;





// Wifi Codes
const char* ssid = "100";
const char* password = "mahdihastam";
String SERVER_IP_ADDRESS = "192.168.1.254";




// Server Allowed To Receive Message
bool allowedToSend = false;


const String ESP_NAME = "ESP_1";



// Response Types
const int RESPONSE_TYPE_CONNECTION = 1;
const int RESPONSE_TYPE_GET = 2;
const int RESPONSE_TYPE_PUT = 3;
const int RESPONSE_TYPE_CHANGE = 4;
const int RESPONSE_TYPE_MESSAGE = 5;
const int RESPONSE_TYPE_CHIP_INFO = 6;
const int RESPONSE_TYPE_MPU_FFT = 7;


// Request Types
const int REQUEST_TYPE_CONNECTION = 1;
const int REQUEST_TYPE_GET = 2;
const int REQUEST_TYPE_PUT = 3;
const int REQUEST_TYPE_CHANGE = 4;
const int REQUEST_TYPE_MESSAGE = 5;
const int REQUEST_TYPE_CHIP_INFO = 6;



TaskHandle_t Task2;


void setup() {

  Serial.begin(115200);
  initI2CBus();
  startMPU();
  initWiFi();
  initWebSocket();
  initOTA();
  initTaksCoreTwo();
  sampling_period_us = 10;
  Serial.print("loop() running on core ");
  Serial.println(xPortGetCoreID());
  delay(2000);
}


void TaskTwoCode(void* parameter) {
  while (true) {
    if (sensorOneActive) {
      getMpuOneData();
    }
    if (sensorTwoActive) {
      getMpuTwoData();
    }
    if (sensorThreeActive) {
      getMpuThreeData();
    }
    if (sensorFourActive) {
      getMpuFourData();
    }
  }
}


void loop() {
  webSocket.loop();
  ArduinoOTA.handle();
  EVERY_N_SECONDS(1) {
    sendMpuesFFTToServer();
  }
}