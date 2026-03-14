#include "display.h"

#include <Arduino.h>

void initDisplay() {
  Serial.begin(9600);
}

void showReading(float value) {
  Serial.print("Sensor reading: ");
  Serial.println(value);
}
