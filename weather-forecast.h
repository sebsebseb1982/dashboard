#ifndef WEATHER_FORECAST_H
#define WEATHER_FORECAST_H

#include <Arduino.h>

class WeatherForecast {
  public:
    int date;
    String icon;
    float min;
    float max;
};

class WeatherForecastService {
  public:
    static WeatherForecast* get();
};

#endif