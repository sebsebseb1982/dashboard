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

void GFX::drawDegreeSymbol(int x, int y, int radius, uint16_t symbolColor, uint16_t backgroundColor) {
  int innerRadius = radius * 0.5;

  if (innerRadius != radius) {
    this->display->fillCircle(
      x,
      y,
      radius,
      symbolColor);
    this->display->fillCircle(
      x,
      y,
      innerRadius,
      backgroundColor);
  } else {
    this->display->drawCircle(
      x,
      y,
      radius,
      symbolColor);
  }
}

void GFX::drawHalftonePoints(int x, int y, int width, int height) {
  int pointDistance = 16;
  int lineCount = 0;

  for (int pointY = y; pointY < y + height; pointY += pointDistance * 0.866) {
    for (int pointX = x; pointX < x + width; pointX += pointDistance) {
      int xOffset = 0;
      if ((lineCount % 2) == 0) {
        xOffset -= (pointDistance * 0.866) / 2;
      }
      float xRatio = (1.0 * (pointX + xOffset - x)) / width;
      this->display->fillCircle(
        pointX + xOffset,
        pointY,
        0.6 * pointDistance * (1.0 - xRatio),
        GxEPD_RED);
    }
    lineCount++;
  }
}

void GFX::greyed(int x, int y, int width, int height, uint16_t color) {
  for (int pointY = y; pointY < y + height; pointY++) {
    for (int pointX = x + y % 2; pointX < x + width; pointX += 2) {
      this->display->drawPixel(
        pointX,
        pointY,
        color);
    }
  }
}

void GFX::darklyGreyed(int x, int y, int width, int height, uint16_t color) {
  for (int pointY = y; pointY < y + height; pointY += 2) {
    this->display->drawLine(
      x,
      pointY,
      x + width,
      pointY,
      color);
  }
  for (int pointX = x; pointX < x + width; pointX += 2) {
    this->display->drawLine(
      pointX,
      y,
      pointX,
      y + height,
      color);
  }
}

void GFX::veryDarklyGreyed(int x, int y, int width, int height, uint16_t color) {
  for (int pointY = y; pointY < y + height; pointY++) {
    if (pointY % 3 == 1 || pointY % 3 == 2) {
      this->display->drawLine(
        x,
        pointY,
        x + width,
        pointY,
        color);
    }
  }
  for (int pointX = x; pointX < x + width; pointX++) {
    if (pointX % 3 == 1 || pointX % 3 == 2) {
      this->display->drawLine(
        pointX,
        y,
        pointX,
        y + height,
        color);
    }
  }
}

void GFX::drawHorizontalSeparator(int x, int y, int width, int thickness, uint16_t color) {
  this->display->fillCircle(
    x,
    y,
    thickness / 2,
    color);

  this->display->fillRect(
    x,
    y - thickness / 2,
    width,
    thickness,
    color);

  this->display->fillCircle(
    x + width,
    y,
    thickness / 2,
    color);
}
void GFX::drawVerticalSeparator(int x, int y, int height, int thickness, uint16_t color) {
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

String GFX::getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
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