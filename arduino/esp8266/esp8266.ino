/*
    This should wake up the esp8266 each hour, connect to the WIFI, get 
    temperature and pressure from the attached BME280 sensor in the D1 and D2
    and send the info the and API.
*/

#include <ESP8266WiFi.h>
#include <SparkFunBME280.h>

// GENERAL
//const int loop_delay = 86400000/24; //1 day has 86400000 milisenconds
const int loop_delay = 10000; //10 secs
BME280 sensor;

// WIFI
const char* ssid     = "xxxx";
const char* password = "xxxx";

boolean isWifiConnected() {

  Serial.print("Connecting to SSID: ");
  Serial.println(ssid);

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  }

  int max_retries = 60;
  int retries;
  
  for (retries = 0; WiFi.status() != WL_CONNECTED and retries < max_retries; ++retries ) {
    delay(1000);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    return true;
  }
  else {
    Serial.print("ERROR: After ");
    Serial.print(retries);
    Serial.print(" retries, the wifi can not connect to SSID: ");
    Serial.println(ssid);
    return false;
  }
}

// SENSOR
boolean isSensorConnected() {
  Wire.begin();

  if (sensor.beginI2C() == false) {
    Serial.println("ERROR: The sensor did not respond. Please check wiring.");
    return false;
  }
  //GET data from the BME280
  //Serial.begin(9600);
  return true;
}

double getSensorTemp() {
  Serial.println("Reading temperature values from BME280");
  double temp = sensor.readTempC();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("ºC");
  return temp;
}

double getSensorPressure() {
  Serial.println("Reading pressure values from BME280");
  double pressure = sensor.readFloatPressure();
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println("mbars");
  return pressure;
}

double getSensorHumidity() {
  Serial.println("Reading humidity values from BME280");
  double humidity = sensor.readFloatHumidity();
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  return humidity;
}

double getSensorAltitude() {
  Serial.println("Reading altitude values from BME280");
  double altitude = sensor.readFloatAltitudeMeters();
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println("meters");
  return altitude;
}


// API
const char* host = "http://api.gorkarevilla.com/";
const char* endpoint   = "meteo/v1/sensor";

boolean sendMetricsData(double temp, double pressure, double humidity) {
  return true;
}


void setup() {
  // Serial.begin(115200);
  Serial.begin(9600);
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);

  Serial.println("-----------------------------------------------------");
  Serial.println("Booting Gteo...");
  Serial.println("-----------------------------------------------------");

}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);
  Serial.println("-----------------------------------------------------");

  if ( isSensorConnected() ) {

    double temp = getSensorTemp();
    double pressure = getSensorPressure();
    double humidity = getSensorHumidity();
    // double altitude = getSensorAltitude();


    if ( isWifiConnected() ) {
      if (sendMetricsData(temp, pressure, humidity) ){

      }
    }

  }

  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  Serial.println("-----------------------------------------------------");

  delay(loop_delay);
}
