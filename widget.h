#ifndef WIDGET_H
#define WIDGET_H
#include <GxEPD2_3C.h>

class Widget {
private:

public:
  int xPosition;
  int yPosition;
  int width;
  int height;
  uint16_t backgroundColor;
  GxEPD2_3C<GxEPD2_750c_Z90, 264> *display;

  Widget(
    int xPosition,
    int yPosition,
    int width,
    int height,
    uint16_t backgroundColor,
    GxEPD2_3C<GxEPD2_750c_Z90, 264> *display);
  virtual void draw(){};
};

#endif