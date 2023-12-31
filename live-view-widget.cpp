#include <GxEPD2_3C.h>

#include "widget.h"
#include "gfx.h"
#include "live-view-widget.h"
#include "home-assistant.h"
#include "date-utils.h"
#include "fonts/fonts.h"
#include "images/weather-forecast/weather-forecast.icons.150x150.h"
#include "images/wind.h"

LiveViewWidget::LiveViewWidget(
  int xPosition,
  int yPosition,
  int width,
  int height,
  uint16_t backgroundColor,
  GxEPD2_3C<GxEPD2_750c_Z90, 264> *display,
  OneWeekWeatherForecast oneWeekWeatherForecast)
  : Widget(
    xPosition,
    yPosition,
    width,
    height,
    backgroundColor,
    display) {
  this->display = display;
  this->gfx = GFX(display);
  this->oneWeekWeatherForecast = oneWeekWeatherForecast;
}

void LiveViewWidget::draw() {


  //"sensor.sun_next_rising"
  //"sensor.sun_next_setting"

  drawDomiticsInformations();
  drawWeatherForecast();
  /*
  gfx.drawHorizontalSeparator(
    50,
    220,
    200,
    7,
    GxEPD_WHITE);*/
  /*drawTemperature(
    outsideTemperature,
    xPosition + 135,
    yPosition + 80);
  drawTemperature(
    weatherForecastTemperature,
    xPosition + 135,
    yPosition + 120);*/
  /*
  int insideTemperatureX = xPosition + (width / 2);
  int insideTemperatureY = yPosition + 100;
  display->setTextColor(GxEPD_WHITE);
  display->setFont(&DejaVu_LGC_Sans_96);*/
  /*gfx.drawCentreString(
    currentTermperature,
    insideTemperatureX,
    insideTemperatureY);
  gfx.drawDegreeSymbol(
    insideTemperatureX + 36,
    insideTemperatureY - 62,
    9,
    GxEPD_WHITE,
    GxEPD_RED);*/
}

void LiveViewWidget::drawWeatherForecast() {
  int xMiddle = xPosition + (width / 2) + 20;
  float weatherForecastTemperature = oneWeekWeatherForecast.days[0].temperature;
  drawBigTemperature(
    weatherForecastTemperature,
    xMiddle,
    yPosition + 205);

  display->setFont(&FreeSans12pt7b);
  String currentDate;
  currentDate += DateUtils::translateDayOfTheWeek(weekday(oneWeekWeatherForecast.days[0].dateTime));
  currentDate += F(" ");
  currentDate += String(day(oneWeekWeatherForecast.days[0].dateTime));
  currentDate += F(" ");
  currentDate += DateUtils::translateMonth(month(oneWeekWeatherForecast.days[0].dateTime));

  gfx.drawCentreString(
    currentDate,
    xMiddle,
    yPosition + 230);

  int iconSize = 150;
  int iconX = xMiddle - iconSize / 2;
  int iconY = yPosition + 10;

  uint16_t iconColor = GxEPD_WHITE;
  String condition = oneWeekWeatherForecast.days[0].condition;
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
  }
}

void LiveViewWidget::drawDomiticsInformations() {
  int xMiddle = xPosition + (width / 2) + 20;
  int gridY = 249;
  int boxSize = 113;
  int boxPadding = 10;

  float insideTemperature = atof(HomeAssistant::getEntityState("sensor.temperature_maison").c_str());
  drawTemperatureBox(
    xMiddle - boxSize - (boxPadding / 2),
    gridY,
    boxSize,
    boxSize,
    "Interieur",
    insideTemperature,
    GxEPD_WHITE);

  float outsideTemperature = atof(HomeAssistant::getEntityState("sensor.domo_exterieur_2").c_str());
  drawTemperatureBox(
    xMiddle + (boxPadding / 2),
    gridY,
    boxSize,
    boxSize,
    "Exterieur",
    outsideTemperature,
    GxEPD_WHITE);

  float setPoint = atof(HomeAssistant::getEntityState("sensor.consigne_thermostat").c_str());
  drawTemperatureBox(
    xMiddle - boxSize - (boxPadding / 2),
    gridY + boxSize + boxPadding,
    boxSize,
    boxSize,
    "Consigne",
    setPoint,
    GxEPD_WHITE);

  drawIconBox(
    xMiddle + (boxPadding / 2),
    gridY + boxSize + boxPadding,
    boxSize,
    boxSize,
    HomeAssistant::getEntityState("input_boolean.etat_ventilation") == "on",
    wind,
    50,
    GxEPD_WHITE,
    GxEPD_RED);
}

void LiveViewWidget::drawTemperature(float temperature, int x, int y) {
  display->setTextColor(GxEPD_WHITE);
  display->setFont(&FreeSans12pt7b);
  String temperatureString;
  temperatureString += String(temperature, 0);
  temperatureString += F(" C");

  gfx.drawRightAlignedString(
    temperatureString,
    x,
    y);
  gfx.drawDegreeSymbol(
    x - 17,
    y - 15,
    2,
    GxEPD_WHITE,
    GxEPD_RED);
}

void LiveViewWidget::drawBigTemperature(float temperature, int x, int y) {
  display->setTextColor(GxEPD_WHITE);
  display->setFont(&DejaVu_LGC_Sans_48);
  String temperatureString;
  temperatureString += String(temperature, 0);
  temperatureString += F(" C");

  gfx.drawCentreString(
    temperatureString,
    x,
    y);
  gfx.drawDegreeSymbol(
    x + 20,
    y - 30,
    6,
    GxEPD_WHITE,
    GxEPD_RED);
}

void LiveViewWidget::drawIconBox(int x, int y, int width, int height, boolean isActive, const unsigned char *icon, int iconSize, uint16_t color, uint16_t backgroundColor) {
  drawBox(
    x,
    y,
    width,
    height,
    color);

  display->drawBitmap(
    x + (width - iconSize) / 2,
    y + (height - iconSize) / 2,
    icon,
    iconSize,
    iconSize,
    color);

  if (!isActive) {
    gfx.darklyGreyed(
      x,
      y,
      width,
      height,
      backgroundColor);
  }
}

void LiveViewWidget::drawTemperatureBox(int x, int y, int width, int height, String label, float temperature, uint16_t color) {
  drawBox(
    x,
    y,
    width,
    height,
    color);

  display->setTextColor(GxEPD_WHITE);
  display->setFont(&FreeSans12pt7b);

  gfx.drawCentreString(
    label,
    x + width / 2,
    y + 40);

  String temperatureString;
  temperatureString += String(temperature, 1);
  temperatureString += F(" C");

  gfx.drawCentreString(
    temperatureString,
    x + width / 2,
    y + 80);

  gfx.drawDegreeSymbol(
    x + (width / 2) + 15,
    y + 65,
    2,
    GxEPD_WHITE,
    GxEPD_RED);
}

void LiveViewWidget::drawBox(int x, int y, int width, int height, uint16_t color) {
  int radius = 12;
  int borderSize = 5;

  display->fillRoundRect(
    x,
    y,
    width,
    height,
    radius,
    color);

  display->fillRoundRect(
    x + borderSize,
    y + borderSize,
    width - (2 * borderSize),
    height - (2 * borderSize),
    radius - borderSize,
    backgroundColor);
}