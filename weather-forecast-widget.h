#ifndef WEATHER_FORECAST_GUI_H
#define WEATHER_FORECAST_GUI_H
#include <GxEPD2_3C.h>
#include "weather-forecast.h"
#include "gfx.h"

const unsigned char clearSky[] = { /*0X00,0X01,0X32,0X00,0X32,0X00,*/
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0XC0,0X00,0X00,
0X00,0X00,0X03,0X00,0XC0,0X30,0X00,0X00,0X00,0X03,0X80,0XC0,0X30,0X00,0X00,0X00,
0X01,0X80,0XC0,0X60,0X00,0X00,0X00,0X00,0XC0,0X00,0XE0,0X00,0X00,0X00,0X00,0XC0,
0X00,0XC0,0X00,0X00,0X00,0X00,0X40,0X00,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X01,0X80,0X01,0XE0,0X00,0X70,0X00,0X01,0XE0,0X0F,0XFC,0X01,0XE0,0X00,
0X00,0X78,0X1F,0XFE,0X03,0X80,0X00,0X00,0X38,0X3F,0XFF,0X03,0X00,0X00,0X00,0X00,
0X7F,0XFF,0X80,0X00,0X00,0X00,0X00,0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0XFF,0XFF,
0XE0,0X00,0X00,0X00,0X01,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X01,0XFF,0XFF,0XE0,0X00,
0X00,0X00,0X03,0XFF,0XFF,0XF0,0X00,0X00,0X0F,0XC3,0XFF,0XFF,0XF0,0XFC,0X00,0X0F,
0XC3,0XFF,0XFF,0XF0,0XFC,0X00,0X00,0X03,0XFF,0XFF,0XF0,0X00,0X00,0X00,0X01,0XFF,
0XFF,0XE0,0X00,0X00,0X00,0X01,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X00,0XFF,0XFF,0XC0,
0X00,0X00,0X00,0X00,0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X7F,0XFF,0X80,0X00,0X00,
0X00,0X38,0X3F,0XFF,0X03,0X00,0X00,0X00,0X70,0X1F,0XFE,0X03,0XC0,0X00,0X01,0XC0,
0X07,0XF8,0X00,0XE0,0X00,0X01,0X80,0X01,0XE0,0X00,0X60,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC0,0X00,0XC0,0X00,
0X00,0X00,0X01,0XC0,0X00,0XE0,0X00,0X00,0X00,0X01,0X80,0XC0,0X60,0X00,0X00,0X00,
0X03,0X80,0XC0,0X30,0X00,0X00,0X00,0X03,0X00,0XC0,0X30,0X00,0X00,0X00,0X00,0X00,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0XC0,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};

class WeatherForecastWidget {
public:
  WeatherForecastWidget(OneWeekWeatherForecast oneWeekWeatherForecast, GxEPD2_3C<GxEPD2_750c_Z90, 264> *display);
  void draw();
private:
  void drawBackground();
  void drawData();
  // TODO à déplacer
  String getDayLabel(time_t date);
  OneWeekWeatherForecast oneWeekWeatherForecast;
  GxEPD2_3C<GxEPD2_750c_Z90, 264> *display;
  GFX gfx;
};

#endif