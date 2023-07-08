#include <GxEPD2_3C.h>
#include <TimeLib.h>

#include "fonts/fonts.h"
#include "weather-forecast.h"
#include "weather-forecast-widget.h"
#include "date-utils.h"
#include "images/weather-forecast/weather-forecast.icons.44x44.h"

WeatherForecastWidget::WeatherForecastWidget(OneWeekWeatherForecast oneWeekWeatherForecast, GxEPD2_3C<GxEPD2_750c_Z90, 264> *display) {
  this->oneWeekWeatherForecast = oneWeekWeatherForecast;
  this->display = display;
  this->gfx = GFX(display);
}

void WeatherForecastWidget::draw() {
  this->drawBackground();
  this->drawData();
}

void WeatherForecastWidget::drawBackground() {
}

void WeatherForecastWidget::drawData() {
  this->display->setTextColor(GxEPD_BLACK);
  this->display->setFont(&FreeSans12pt7b);

  int startX = 490;
  int startY = 25;

  for (int dayIndex = 1; dayIndex < 7; dayIndex++) {
    int date = this->oneWeekWeatherForecast.days[dayIndex].date;
    String currentDay;
    currentDay += DateUtils::translateDayOfTheWeek(weekday(date));
    currentDay += F(" ");
    currentDay += String(day(date));
    currentDay += F("/");
    currentDay += String(month(date));
    //currentDay += this->oneWeekWeatherForecast.days[dayIndex].icon;
    display->setCursor(
      startX,
      startY + (dayIndex * 50));
    display->print(currentDay);

    int iconX = startX + 210;
    int iconY = startY + (dayIndex * 50) - 35;
    int iconSize = 44;
    String icon = this->oneWeekWeatherForecast.days[dayIndex].icon;
    if (icon.startsWith("01")) {
      display->drawBitmap(
        iconX,
        iconY,
        clear_sky,
        iconSize,
        iconSize,
        GxEPD_RED);
    } else if (icon.startsWith("02")) {
      display->drawBitmap(
        iconX,
        iconY,
        few_clouds,
        iconSize,
        iconSize,
        GxEPD_RED);
    } else if (icon.startsWith("03")) {
      display->drawBitmap(
        iconX,
        iconY,
        scattered_clouds,
        iconSize,
        iconSize,
        GxEPD_RED);
    } else if (icon.startsWith("04")) {
      display->drawBitmap(
        iconX,
        iconY,
        broken_clouds,
        iconSize,
        iconSize,
        GxEPD_RED);
    } else if (icon.startsWith("09")) {
      display->drawBitmap(
        iconX,
        iconY,
        shower_rain,
        iconSize,
        iconSize,
        GxEPD_RED);
    } else if (icon.startsWith("10")) {
      display->drawBitmap(
        iconX,
        iconY,
        rain,
        iconSize,
        iconSize,
        GxEPD_RED);
    } else if (icon.startsWith("11")) {
      display->drawBitmap(
        iconX,
        iconY,
        thunderstorm,
        iconSize,
        iconSize,
        GxEPD_RED);
    } else if (icon.startsWith("13")) {
      display->drawBitmap(
        iconX,
        iconY,
        snow,
        iconSize,
        iconSize,
        GxEPD_RED);
    } else if (icon.startsWith("50")) {
      display->drawBitmap(
        iconX,
        iconY,
        mist,
        iconSize,
        iconSize,
        GxEPD_RED);
    }

    String currentTermperature;
    currentTermperature += String(this->oneWeekWeatherForecast.days[dayIndex].max, 0);
    currentTermperature += F(" C");
    int temperatureX = startX + 280;
    int temperatureY = startY + (dayIndex * 50);
    display->setCursor(
      temperatureX,
      temperatureY);
    display->print(currentTermperature);
    gfx.drawDegreeSymbol(
      temperatureX + 29,
      temperatureY - 15,
      2,
      GxEPD_BLACK,
      GxEPD_WHITE);
  }
}