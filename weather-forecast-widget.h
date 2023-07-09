#ifndef WEATHER_FORECAST_GUI_H
#define WEATHER_FORECAST_GUI_H
#include <GxEPD2_3C.h>
#include "weather-forecast.h"
#include "gfx.h"

class WeatherForecastWidget {
public:
  WeatherForecastWidget(OneWeekWeatherForecast oneWeekWeatherForecast, GxEPD2_3C<GxEPD2_750c_Z90, 264> *display);
  void draw();
private:
  void drawBackground();
  void drawData();
  OneWeekWeatherForecast oneWeekWeatherForecast;
  GxEPD2_3C<GxEPD2_750c_Z90, 264> *display;
  GFX gfx;
};

#endif