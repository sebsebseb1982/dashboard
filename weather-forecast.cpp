#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <TimeLib.h>

#include "arduino_secrets.h"
#include "common.h"
#include "weather-forecast.h"

WeatherForecast::WeatherForecast() {}
WeatherForecast::WeatherForecast(time_t dateTime, String condition, float temperature, float temperatureLow, float precipitation) {
  this->dateTime = dateTime;
  this->condition = condition;
  this->temperature = temperature;
  this->temperatureLow = temperatureLow;
  this->precipitation = precipitation;
}

OneWeekWeatherForecast WeatherForecastService::get() {
  OneWeekWeatherForecast oneWeekWeatherForecast;
  HTTPClient http;
  String homeAssistantWeatherURL;
  homeAssistantWeatherURL += F("http://");
  homeAssistantWeatherURL += SECRET_HOME_ASSISTANT_HOST;
  homeAssistantWeatherURL += F("/api/states/weather.talence");
  http.begin(homeAssistantWeatherURL);

  String bearer;
  bearer += F("Bearer ");
  bearer += SECRET_HOME_ASSISTANT_TOKEN;
  http.addHeader("Authorization", bearer);

  String message;
  message += F("Récupération de la météo");
  message += F(" (GET ");
  message += homeAssistantWeatherURL;
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

    for (int dayIndex = 0; dayIndex < 7; dayIndex++) {
      TimeElements tm = {};
      int parsedYear, parsedMonth, parsedDay;
      const char* datetime = doc["attributes"]["forecast"][dayIndex]["datetime"];
      sscanf(datetime, "%d-%d-%dT", &parsedYear, &parsedMonth, &parsedDay);
      tm.Year = CalendarYrToTm(parsedYear);
      tm.Month = parsedMonth;
      tm.Day = parsedDay;
      time_t parsedDatetime = makeTime(tm);

      String condition = doc["attributes"]["forecast"][dayIndex]["condition"];

      oneWeekWeatherForecast.days[dayIndex] = {
        parsedDatetime,
        condition,
        doc["attributes"]["forecast"][dayIndex]["temperature"],
        doc["attributes"]["forecast"][dayIndex]["templow"],
        doc["attributes"]["forecast"][dayIndex]["precipitation"]
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