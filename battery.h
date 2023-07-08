#ifndef BATTERY_H
#define BATTERY_H

#define BATTERY_VOLTAGE_PIN 33

class Battery {
public:
  static float measureVoltage();
private:
};

#endif
