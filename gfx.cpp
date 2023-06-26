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

void GFX::drawRightAlignedString(const String buf, int x, int y) {
  int16_t x1, y1;
  uint16_t w, h;
  this->display->getTextBounds(buf, 0, 0, &x1, &y1, &w, &h);

  this->display->setCursor(x - w, y);
  this->display->print(buf);
}

void GFX::drawFloatingText(const String &buf, int x, int y, int maxWidth, int &height) {
  int wordIndex = 0;
  int lineIndex = 0;
  String nextWord = getValue(buf, ' ', wordIndex);

  String previousLine;
  String currentLine;

  int16_t x1, y1;
  uint16_t w, h;

  while (nextWord != "") {
    if (currentLine != " ") {
      currentLine += F(" ");
    }
    currentLine += nextWord;

    this->display->getTextBounds(currentLine, 0, 0, &x1, &y1, &w, &h);

    if (w > maxWidth) {
      this->display->setCursor(x, y + (lineIndex * LINE_HEIGHT));
      this->display->print(previousLine);
      currentLine = "";
      previousLine = "";
      lineIndex++;
    } else {
      previousLine = currentLine;
      wordIndex++;
      nextWord = getValue(buf, ' ', wordIndex);
    }
  }

  this->display->setCursor(x, y + (lineIndex * LINE_HEIGHT));
  this->display->print(previousLine);

  height = (lineIndex + 1) * LINE_HEIGHT;
}

String GFX::getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}