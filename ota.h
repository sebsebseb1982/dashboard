#ifndef OTA_H
#define OTA_H

#define ENABLE_OTA_BUTTON_PIN 18

class OTA {
  public:
    static void setup();
    static void loop();
    static boolean isEnabled();
};

#endif