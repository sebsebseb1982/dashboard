#ifndef WEATHER_FORECAST_H
#define WEATHER_FORECAST_H

#include <Arduino.h>

class WeatherForecast {
public:
  WeatherForecast();
  WeatherForecast(int date, String icon, float min, float max);
  int date;
  String icon;
  float min;
  float max;
};

struct OneWeekWeatherForecast {
    WeatherForecast days[7];
};

class WeatherForecastService {
public:
  static OneWeekWeatherForecast get();
};

#endif