#include "display.h"
#include "sensor.h"

void setup() {
  initDisplay();
  initSensor();
}

void loop() {
  const float reading = readSensorValue();
  showReading(reading);
  delay(1000);
}
