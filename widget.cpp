#include <arduino.h>
#include <GxEPD2_3C.h>
#include "widget.h"


Widget::Widget(
  int xPosition,
  int yPosition,
  int width,
  int height,
  uint16_t backgroundColor,
  GxEPD2_3C<GxEPD2_750c_Z90, 264> *display) {
  this->xPosition = xPosition;
  this->yPosition = yPosition;
  this->width = width;
  this->height = height;
  this->backgroundColor = backgroundColor;
  this->display = display;
}