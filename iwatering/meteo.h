
/*
 * 
 * @author: Andrea Pagliarani
 * @since: 25/07/2021
 * 
 * This is an Arduino project aimed at building an
 * automated watering plant with an ESP8266
 * 
 */


#include "arduino_secrets.h"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>


const String SERVER_NAME = "http://api.openweathermap.org";

String getMeteo() {

  String payload = "";

  if (WiFi.status() == WL_CONNECTED) {
    
    WiFiClient wifiClient; 
    
    HTTPClient http;

    String serverPath = SERVER_NAME + "/data/2.5/weather?q=" + CITY + "&appid=" + SECRET_APPID;
    http.begin(wifiClient, serverPath);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      payload = http.getString();
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
    return payload;
  } else {
    Serial.println("WiFi Disconnected");
  }
}

bool isRaining(String meteoResponse) {

  DynamicJsonDocument meteo(1024);
  deserializeJson(meteo, meteoResponse);
  
  String weather = meteo["weather"][0]["main"];
  if (!weather.equals("Rain") && !weather.equals("Thunderstorm")) {
    return false;
  } else {
    return true;
  }
  
}
