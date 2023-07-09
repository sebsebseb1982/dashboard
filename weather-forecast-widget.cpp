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
    time_t dateTime = this->oneWeekWeatherForecast.days[dayIndex].dateTime;
    String currentDay;
    currentDay += DateUtils::translateDayOfTheWeek(weekday(dateTime));
    currentDay += F(" ");
    currentDay += String(day(dateTime));
    currentDay += F("/");
    currentDay += String(month(dateTime));
    display->setCursor(
      startX,
      startY + (dayIndex * 50));
    display->print(currentDay);

    int iconX = startX + 210;
    int iconY = startY + (dayIndex * 50) - 35;
    int iconSize = 44;
    uint16_t iconColor = GxEPD_RED;
    String condition = this->oneWeekWeatherForecast.days[dayIndex].condition;
    if (condition.equals("sunny")) {
      display->drawBitmap(
        iconX,
        iconY,
        sunny,
        iconSize,
        iconSize,
        iconColor);
    } else if (condition.equals("partlycloudy")) {
      display->drawBitmap(
        iconX,
        iconY,
        partlycloudy,
        iconSize,
        iconSize,
        iconColor);
    } else if (condition.equals("cloudy")) {
      display->drawBitmap(
        iconX,
        iconY,
        cloudy,
        iconSize,
        iconSize,
        iconColor);
    } else if (condition.equals("fog")) {
      display->drawBitmap(
        iconX,
        iconY,
        fog,
        iconSize,
        iconSize,
        iconColor);
    } else if (condition.equals("hail")) {
      display->drawBitmap(
        iconX,
        iconY,
        hail,
        iconSize,
        iconSize,
        iconColor);
    } else if (condition.equals("lightning")) {
      display->drawBitmap(
        iconX,
        iconY,
        lightning,
        iconSize,
        iconSize,
        iconColor);
    } else if (condition.equals("lightningrainy")) {
      display->drawBitmap(
        iconX,
        iconY,
        lightningrainy,
        iconSize,
        iconSize,
        iconColor);
    } else if (condition.equals("pouring")) {
      display->drawBitmap(
        iconX,
        iconY,
        pouring,
        iconSize,
        iconSize,
        iconColor);
    } else if (condition.equals("rainy")) {
      display->drawBitmap(
        iconX,
        iconY,
        rainy,
        iconSize,
        iconSize,
        iconColor);
    } else if (condition.equals("snowy")) {
      display->drawBitmap(
        iconX,
        iconY,
        snowy,
        iconSize,
        iconSize,
        iconColor);
    } else if (condition.equals("snowyrainy")) {
      display->drawBitmap(
        iconX,
        iconY,
        snowyrainy,
        iconSize,
        iconSize,
        iconColor);
    } else {
      display->setCursor(
        iconX,
        iconY);
      display->print(condition);
    }

    String currentTermperature;
    currentTermperature += String(this->oneWeekWeatherForecast.days[dayIndex].temperature, 0);
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