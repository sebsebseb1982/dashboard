#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>

#include "fonts/fonts.h"
#include "wifi-connection.h"
#include "ota.h"
#include "weather-forecast.h"
#include "weather-forecast-widget.h"
#include "home-assistant.h"
#include "quote-of-the-day.h"
#include "quote-of-the-day-widget.h"
#include "live-view-widget.h"
#include "common.h"
#include "gfx.h"
#include "battery.h"

// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0
#define REFRESH_RATE_IN_MINUTES 59

GxEPD2_3C< GxEPD2_750c_Z90, GxEPD2_750c_Z90::HEIGHT / 2 > display(GxEPD2_750c_Z90(/*CS=*/15, /*DC=*/27, /*RST=*/26, /*BUSY=*/25));  // GDEH075Z90 880x528
boolean batteryCharging = false;
float batteryVoltage;
unsigned long nextRefresh;
boolean otaEnabled = false;

void setup() {
  Serial.begin(115200);

  batteryVoltage = Battery::measureVoltage();
  batteryCharging = batteryVoltage < 5;

  WiFiConnection::setup();

  display.init(115200);  // uses standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  // *** special handling for Waveshare ESP32 Driver board *** //
  // ********************************************************* //
  SPI.end();  // release standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  //SPI: void begin(int8_t sck=-1, int8_t miso=-1, int8_t mosi=-1, int8_t ss=-1);
  SPI.begin(13, 12, 14, 15);  // map and init SPI pins SCK(13), MISO(12), MOSI(14), SS(15)
                              // *** end of special handling for Waveshare ESP32 Driver board *** //
                              // **************************************************************** //

  if (OTA::isEnabled()) {
    OTA::setup();
    otaEnabled = true;
  }

  nextRefresh = millis();
}

void refreshScreen() {
  display.setFullWindow();
  display.firstPage();
  do {

    display.fillScreen(GxEPD_WHITE);

    int verticalSplitX = SCREEN_WIDTH / 3;
    int horizontalSplitY = 350;
    OneWeekWeatherForecast oneWeekWeatherForecast = WeatherForecastService::get();

    // Quote of the day
    QuoteOfTheDayWidget quoteOfTheDayWidget(
      verticalSplitX,
      horizontalSplitY,
      SCREEN_WIDTH - verticalSplitX,
      SCREEN_HEIGHT - horizontalSplitY,
      GxEPD_WHITE,
      &display,
      QuoteOfTheDayService::get());
    quoteOfTheDayWidget.draw();

    // Halftone points
    GFX gfx(&display);
    gfx.drawHalftonePoints(
      verticalSplitX,
      0,
      200,
      SCREEN_HEIGHT + 10);

    // Live view
    LiveViewWidget liveViewWidget(
      0,
      0,
      verticalSplitX - 1,
      SCREEN_HEIGHT,
      GxEPD_RED,
      &display,
      oneWeekWeatherForecast);
    liveViewWidget.draw();

    // One week weather forecast
    WeatherForecastWidget weatherForecastWidget(
      oneWeekWeatherForecast,
      &display);
    weatherForecastWidget.draw();

    display.setTextColor(GxEPD_WHITE);
    display.setFont(&FreeSans9pt7b);
    display.setCursor(0, 13);
    String temp;
    if (otaEnabled) {
      temp += "OTA";
      temp += F(" ");
      temp += String(batteryVoltage, 2);
      temp += F("v");
    }

    display.print(temp);

  } while (display.nextPage());
}

void loop() {
  batteryVoltage = Battery::measureVoltage();
  batteryCharging = batteryVoltage < 5;

  if (!otaEnabled) {
    refreshScreen();
    display.powerOff();

    esp_sleep_enable_timer_wakeup(REFRESH_RATE_IN_MINUTES * 60e6);
    Serial.print("Going back to sleep for ");
    Serial.print(REFRESH_RATE_IN_MINUTES);
    Serial.println(" minutes.");
    Serial.flush();
    esp_deep_sleep_start();
  }

  WiFiConnection::loop();
  OTA::loop();

  if (millis() > nextRefresh) {
    nextRefresh = millis() + REFRESH_RATE_IN_MINUTES * 60e6;
    refreshScreen();
  }
}