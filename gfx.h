#ifndef GFX_H
#define GFX_H

#include <GxEPD2_3C.h>
#define LINE_HEIGHT 18

class GFX {
public:
  GFX();
  GFX(GxEPD2_3C<GxEPD2_750c_Z90, 264> *display);
  void drawCentreString(const String &buf, int x, int y);
  void drawRightAlignedString(const String buf, int x, int y);
  void drawFloatingText(const String &buf, int x, int y, int maxWidth, int &height);
private:
  GxEPD2_3C<GxEPD2_750c_Z90, 264> *display;
  String getValue(String data, char separator, int index);
};

#endif