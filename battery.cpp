#include <arduino.h>
#include "battery.h"

float Battery::measureVoltage() {
  pinMode(BATTERY_VOLTAGE_PIN, INPUT);
  return ((float)analogRead(BATTERY_VOLTAGE_PIN)) * 0.002765;
}