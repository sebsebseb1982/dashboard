#ifndef GFX_H
#define GFX_H
#include <GxEPD2_3C.h>

class GFX {
public:
  GFX();
  GFX(GxEPD2_3C<GxEPD2_750c_Z90, 264> *display);
  void drawCentreString(const String &buf, int x, int y);
private:
  GxEPD2_3C<GxEPD2_750c_Z90, 264> *display;
};

#endif