#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "arduino_secrets.h"
#include "common.h"
#include "weather-forecast.h"

WeatherForecast::WeatherForecast() {}
WeatherForecast::WeatherForecast(int date, String icon, float min, float max) {
  this->date = date;
  this->icon = icon;
  this->min = min;
  this->max = max;
}

OneWeekWeatherForecast WeatherForecastService::get() {
  OneWeekWeatherForecast oneWeekWeatherForecast;
  HTTPClient http;
  http.begin(SECRET_API_OPENWEATHERMAP, SECRET_ROOT_CA);

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