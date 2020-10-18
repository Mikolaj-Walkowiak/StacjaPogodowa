#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <ArduinoJson.h>

// Set your access point network credentials
const char* ssid = "SKOSZTUJ";
const char* password = "ZamknijDrzwiOdZewnatrz2137";

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

char output[200];

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  IPAddress ip(192,168,1,223);
  IPAddress gateway(192,168,1,1);   
  IPAddress subnet(255,255,255,0);   
  WiFi.config(ip, gateway, subnet);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  bool status;

  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}
 
void loop() {
  StaticJsonDocument<200> doc;

  doc["weather"]["temp"] = bme.readTemperature()+273.15;
  doc["weather"]["humidity"] = bme.readHumidity();
  doc["weather"]["pressure"] = bme.readPressure()/100.0;
  
  serializeJson(doc, output, 200);
  HTTPClient http;    //Declare object of class HTTPClient

  http.begin("http://192.168.1.222/data");              //Specify request destination
  http.addHeader("Content-Type", "application/json");    //Specify content-type header

  int httpCode = http.POST(output);   //Send the request
  http.end();  //Close connection
  
  delay(5000);
}
