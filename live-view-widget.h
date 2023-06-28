#ifndef LIVE_VIEW_WIDGET_H
#define LIVE_VIEW_WIDGET_H

#include <GxEPD2_3C.h>

#include "widget.h"
#include "gfx.h"
#include "weather-forecast.h"

class LiveViewWidget : public Widget {
public:
  LiveViewWidget(
    int xPosition,
    int yPosition,
    int width,
    int height,
    uint16_t backgroundColor,
    GxEPD2_3C<GxEPD2_750c_Z90, 264> *display,
    OneWeekWeatherForecast oneWeekWeatherForecast);
  void draw();
private:
  GxEPD2_3C<GxEPD2_750c_Z90, 264> *display;
  GFX gfx;
  OneWeekWeatherForecast oneWeekWeatherForecast;
  void drawWeatherForecast();
  void drawDomiticsInformations();
  void drawTemperature(float temperature, int x, int y);
  void drawBigTemperature(float temperature, int x, int y);
  void drawIconBox(int x, int y, int width, int height, boolean isActive, const unsigned char *icon, int iconSize, uint16_t color, uint16_t backgroundColor);
  void drawTemperatureBox(int x, int y, int width, int height, String label, float temperature, uint16_t color);
  void drawBox(int x, int y, int width, int height, uint16_t color);
};

#endif