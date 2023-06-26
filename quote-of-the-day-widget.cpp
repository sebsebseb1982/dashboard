#include <GxEPD2_3C.h>
#include "common.h"
#include "widget.h"
#include "quote-of-the-day-widget.h"
#include "quote-of-the-day.h"
#include "quote-of-the-day.icons.h"
#include "gfx.h"
#include "fonts/fonts.h"

QuoteOfTheDayWidget::QuoteOfTheDayWidget(
  int xPosition,
  int yPosition,
  int width,
  int height,
  uint16_t backgroundColor,
GxEPD2_3C<GxEPD2_750c_Z90, 264> *display,
    QuoteOfTheDay quoteOfTheDay)
  : Widget(
    xPosition,
    yPosition,
    width,
    height,
    backgroundColor,
    display) {
  this->quoteOfTheDay = quoteOfTheDay;
  this->display = display;
  this->gfx = GFX(display);
}

void QuoteOfTheDayWidget::draw() {
  int y = 380;

  this->display->setTextColor(GxEPD_BLACK);
  this->display->setFont(&FreeSans9pt7b);

  this->display->drawBitmap(450, y - 40, quoteTop, 64, 64, GxEPD_RED);

  int height;
  int margin = 80;
  this->gfx.drawFloatingText(
    quoteOfTheDay.quote,
    (SCREEN_WIDTH / 2) + margin,
    y,
    (SCREEN_WIDTH / 2) - (2 * margin),
    height);

  this->display->setTextColor(GxEPD_RED);
  this->display->setFont(&FreeSans9pt7b);
  String author;
  author += F("- ");
  author += quoteOfTheDay.author;

  this->display->drawBitmap(800, y + height - 20, quoteBottom, 64, 64, GxEPD_RED);

  this->gfx.drawRightAlignedString(author, SCREEN_WIDTH - 100, y + height + 20);
}
