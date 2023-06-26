#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>

#include "fonts/fonts.h"
#include "wifi-connection.h"
#include "ota.h"
#include "weather-forecast.h"
#include "weather-forecast-widget.h"
#include "weather-forecast.icons.h"
#include "home-assistant.h"
#include "quote-of-the-day.h"
#include "quote-of-the-day-widget.h"
#include "common.h"

// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

GxEPD2_3C< GxEPD2_750c_Z90, GxEPD2_750c_Z90::HEIGHT / 2 > display(GxEPD2_750c_Z90(/*CS=*/15, /*DC=*/27, /*RST=*/26, /*BUSY=*/25));  // GDEH075Z90 880x528

void drawCentreString(const String &buf, int x, int y) {
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(buf, x, y, &x1, &y1, &w, &h);
  display.setCursor(x - w / 2, y);
  display.print(buf);
}



void setup() {
  Serial.begin(115200);
  WiFiConnection::setup();
  OTA::setup();

  display.init(115200);  // uses standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  // *** special handling for Waveshare ESP32 Driver board *** //
  // ********************************************************* //
  SPI.end();  // release standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  //SPI: void begin(int8_t sck=-1, int8_t miso=-1, int8_t mosi=-1, int8_t ss=-1);
  SPI.begin(13, 12, 14, 15);  // map and init SPI pins SCK(13), MISO(12), MOSI(14), SS(15)
                              // *** end of special handling for Waveshare ESP32 Driver board *** //
                              // **************************************************************** //

  display.setFullWindow();
  display.firstPage();
  do {

    display.fillScreen(GxEPD_WHITE);
    display.fillRect(
      0,
      0,
      SCREEN_WIDTH / 2,
      SCREEN_HEIGHT,
      GxEPD_RED);


    /*
    display.setFont(&FreeSans9pt7b);
    drawCentreString(HelloEpaper, 200, 100);

    
    //drawCentreString(HelloEpaper, 200, 200);

    display.setFont(&DejaVu_LGC_Sans_48);
    //drawCentreString(HelloEpaper, 200, 300);

    display.setFont(&DejaVu_LGC_Sans_72);
    //drawCentreString(HelloEpaper, 200, 400);

    display.setFont(&DejaVu_LGC_Sans_96);
    //drawCentreString(HelloEpaper, 200, 500);
    
*/

    String temperature = HomeAssistant::getEntityState("sensor.temperature_maison");

    drawCentreString(
      temperature,
      200,
      420);

    // One week weather forecast
    OneWeekWeatherForecast oneWeekWeatherForecast = WeatherForecastService::get();
    WeatherForecastWidget weatherForecastWidget(
      oneWeekWeatherForecast,
      &display);
    weatherForecastWidget.draw();

    // Quote of the day
    QuoteOfTheDayWidget quoteOfTheDayWidget(
      QuoteOfTheDayService::get(),
      &display);
    quoteOfTheDayWidget.draw();
  } while (display.nextPage());
}

void loop() {
  WiFiConnection::loop();
  OTA::loop();
}