#ifndef QUOTE_OF_THE_DAY_WIDGET_H
#define QUOTE_OF_THE_DAY_WIDGET_H
#include <GxEPD2_3C.h>

#include "widget.h"
#include "quote-of-the-day.h"
#include "gfx.h"

class QuoteOfTheDayWidget : public Widget {
public:
  QuoteOfTheDayWidget(
    int xPosition,
    int yPosition,
    int width,
    int height,
    uint16_t backgroundColor,
    GxEPD2_3C<GxEPD2_750c_Z90, 264> *display,
    QuoteOfTheDay quoteOfTheDay);
  void draw();
private:
  QuoteOfTheDay quoteOfTheDay;
  GxEPD2_3C<GxEPD2_750c_Z90, 264> *display;
  GFX gfx;
};

#endif