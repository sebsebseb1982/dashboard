#include <GxEPD2_3C.h>
#include <TimeLib.h>
#include <Fonts/FreeSans12pt7b.h>

#include "weather-forecast.h"
#include "weather-forecast-widget.h"
#include "fonts/32.h"

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

// TODO à déplacer
String WeatherForecastWidget::getDayLabel(time_t date) {
  switch (weekday(date)) {
    case 1:
      return "Dimanche";
      break;

    case 2:
      return "Lundi";
      break;

    case 3:
      return "Mardi";
      break;

    case 4:
      return "Mercredi";
      break;

    case 5:
      return "Jeudi";
      break;

    case 6:
      return "Vendredi";
      break;

    case 7:
      return "Samedi";
      break;

    default:
      return "???";
      break;
  }
}

void WeatherForecastWidget::drawData() {
  this->display->setTextColor(GxEPD_BLACK);
  this->display->setFont(&FreeSans12pt7b);

  int startX = 490;
  int startY = 25;

  for (int dayIndex = 1; dayIndex < 7; dayIndex++) {
    int date = this->oneWeekWeatherForecast.days[dayIndex].date;
    String currentDay;
    currentDay += this->getDayLabel(date);
    currentDay += F(" ");
    currentDay += String(day(date));
    currentDay += F("/");
    currentDay += String(month(date));
    display->setCursor(
      startX,
      startY + (dayIndex * 50));
    display->print(currentDay);

    display->drawBitmap(
      startX + 210,
      startY + (dayIndex * 50) - 35,
      clearSky,
      50,
      50,
      GxEPD_RED);

    String currentTermperature;
    currentTermperature += String(this->oneWeekWeatherForecast.days[dayIndex].max, 0);
    currentTermperature += F(" C");
    display->setCursor(
      startX + 280,
      startY + (dayIndex * 50));
    display->print(currentTermperature);
  }
}