#ifndef WEATHER_FORECAST_H
#define WEATHER_FORECAST_H

#include <Arduino.h>
#include <TimeLib.h>

class WeatherForecast {
public:
  WeatherForecast();
  WeatherForecast(time_t dateTime, String condition, float temperature, float temperatureLow, float precipitation);
  time_t dateTime;
  String condition;
  float temperature;
  float temperatureLow;
  float precipitation;
};

struct OneWeekWeatherForecast {
  WeatherForecast days[7];
};

class WeatherForecastService {
public:
  static OneWeekWeatherForecast get();
};

#endif