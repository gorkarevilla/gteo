/*
    This should wake up the esp8266 each hour, connect to the WIFI, get 
    temperature and pressure from the attached BME280 sensor in the D1 and D2
    and send the info the and API.
*/

#include <ESP8266WiFi.h>
#include <SparkFunBME280.h>

// WIFI
const char* ssid     = "your-ssid";
const char* password = "your-password";

// SENSOR

// API
const char* host = "http://api.gorkarevilla.com/";
const char* endpoint   = "meteo/v1/sensor";

// GENERAL
const int loop_delay= 86400000/24; //1 day has 86400000 milisenconds
BME280 sensor;


void setup() {
  Serial.begin(115200);
  delay(10);

}

void loop() {
  Serial.print("-----------------------------------------------------");
  Serial.print("Connecting to SSID: ");
  Serial.println(ssid);

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  }

  int max_retries = 10;
  
  for (int retries = 0; WiFi.status() != WL_CONNECTED and retries < max_retries; ++retries ) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    //GET data from the BME280
    Serial.begin(9600);
    Serial.println("Reading basic values from BME280");

    Wire.begin();

    if (sensor.beginI2C() == false) {
      Serial.println("The sensor did not respond. Please check wiring.");
      while(1); //Freeze
    }

  }
  
  Serial.print("-----------------------------------------------------");

  delay(loop_delay);
}
