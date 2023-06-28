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
  void drawDegreeSymbol(int x, int y, int diameter, uint16_t symbolColor, uint16_t backgroundColor);
  void drawHalftonePoints(int x, int y, int width, int height);
  void greyed(int x, int y, int width, int height, uint16_t color);
  void darklyGreyed(int x, int y, int width, int height, uint16_t color);
  void veryDarklyGreyed(int x, int y, int width, int height, uint16_t color);
  void drawHorizontalSeparator(int x, int y, int width, int thickness, uint16_t color);
  void drawVerticalSeparator(int x, int y, int height, int thickness, uint16_t color);

private:
  GxEPD2_3C<GxEPD2_750c_Z90, 264> *display;
  String getValue(String data, char separator, int index);
};

#endif