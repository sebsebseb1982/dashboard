#include "gfx.h"

GFX::GFX() {}

GFX::GFX(GxEPD2_3C<GxEPD2_750c_Z90, 264> *display) {
  this->display = display;
}

void GFX::drawCentreString(const String &buf, int x, int y) {
  int16_t x1, y1;
  uint16_t w, h;
  this->display->getTextBounds(buf, x, y, &x1, &y1, &w, &h);
  this->display->setCursor(x - w / 2, y);
  this->display->print(buf);
}