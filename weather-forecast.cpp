#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "arduino_secrets.h"
#include "common.h"
#include "weather-forecast.h"

WeatherForecast* WeatherForecastService::get() {
  WeatherForecast* weatherForecast = new WeatherForecast[7];
  HTTPClient http;
  http.begin(SECRET_API_OPENWEATHERMAP, root_ca);

  String message;
  message += F("Récupération de la météo");
  message += F(" (GET ");
  message += SECRET_API_OPENWEATHERMAP;
  message += F(")");
  Serial.println(message);

  int httpCode;
  int retry = 0;

  do {
    httpCode = http.GET();
    retry ++;
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
      return weatherForecast;
    }

    return weatherForecast;

  } else {
    String error;
    error += F("KO -> code erreur = ");
    error += String(httpCode);
    Serial.println(error);
    Serial.println("");
    return weatherForecast;
  }
}