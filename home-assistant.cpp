#include "common.h"
#include "home-assistant.h"

HomeAssistant::get() {
  HTTPClient http;

String entity = "sensor.temperature_maison";

String homeAssistantURL;
homeAssistantURL += F("http://");
homeAssistantURL += SECRET_HOME_ASSISTANT_HOST;
homeAssistantURL += F("/api/states/");
homeAssistantURL += entity;

  http.begin(homeAssistantURL);

  int httpCode;
  int retry = 0;

  do {
    httpCode = http.GET();
    retry++;
    Serial.println("...");
  } while (httpCode <= 0 && retry < HTTP_RETRY);

  if (httpCode > 0) {
    Serial.println("OK");
    Serial.println("");

    String response = http.getString();
    http.end();
    DynamicJsonDocument doc(8192);
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return oneWeekWeatherForecast;
    }

    for (int day = 0; day < 7; day++) {
      oneWeekWeatherForecast.days[day] = {
        doc["daily"][day]["dt"],
        doc["daily"][day]["weather"][0]["icon"],
        doc["daily"][day]["temp"]["min"],
        doc["daily"][day]["temp"]["max"] 
        };
    }

    return oneWeekWeatherForecast;

  } else {
    String error;
    error += F("KO -> code erreur = ");
    error += String(httpCode);
    Serial.println(error);
    Serial.println("");
    return oneWeekWeatherForecast;
  }
}