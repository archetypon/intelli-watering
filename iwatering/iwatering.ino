
/*
 * 
 * @author: Andrea Pagliarani
 * @since: 25/07/2021
 * 
 * This is an Arduino project aimed at building an
 * automated watering plant with an ESP8266
 * 
 */


#include <ESP8266WiFi.h> //ESP8266
#include "arduino_secrets.h"
#include "meteo.h"

const int OUT_PIN_1 = 14;
const int SENSOR_PIN = 0;
const int OUT_PIN_2 = 12;
//below this voltage start watering
const float VOLT_LIMIT = 1.9;

void setup() {

  Serial.begin(115200);
  Serial.println("Setting up...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(SECRET_SSID, SECRET_PWD);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(OUT_PIN_1, OUTPUT);
  pinMode(OUT_PIN_2, OUTPUT);
  digitalWrite(OUT_PIN_1, HIGH);
  digitalWrite(OUT_PIN_2, HIGH);
  checkStatus();
  ESP.deepSleep(5.2e9);
  

}

void checkStatus() {
  //read sensor
  int sensorVal = analogRead(SENSOR_PIN);
  float currentVoltage = (sensorVal / 1024.0) * 3.3;
  Serial.println(currentVoltage);
  //get meteo from openweather API
  String meteo = getMeteo();
  boolean raining = isRaining(meteo);
  if(!raining && currentVoltage < VOLT_LIMIT) {
      Serial.println("Start watering");
      digitalWrite(OUT_PIN_1, LOW);
      digitalWrite(OUT_PIN_2, LOW);
      delay(5 * 60000);
      digitalWrite(OUT_PIN_1, HIGH);
      digitalWrite(OUT_PIN_2, HIGH);
  } else {
    Serial.println("Moisture level ok");
  }
}

void loop() {

}
