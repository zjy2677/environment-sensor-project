#include "display.h"
#include "sensor.h"

void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  Serial.begin(9600);
  dht_sensor.begin();

  // for active-LOW digit control: HIGH = off
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
}

void loop() {
  float temperature = dht_sensor.readTemperature();
  float humidity = dht_sensor.readHumidity();

  if (isnan(temperature)) {
    Serial.println("Failed to read temperature");
    return;
  }
  
  if (isnan(humidity)) {
    Serial.println("Failed to read humidity");
    return;
  }
  //Deal with Temperature 
  int temp10 = (int)(temperature * 10 + 0.5);
  int hundreds = (int)(temp10 / 100);
  int tens = (int)((temp10 / 10) % 10);
  int ones = (int)(temp10 % 10);
  // Deal with humidity 
  
  int humidity_int = (int)(humidity + 0.5);
  int humd_tens = (int)(humidity_int / 10);
  int humd_ones = (int)(humidity_int % 10);

  Serial.print("Temperature: ");
  Serial.println(temperature);
 
  Serial.print("Humidity: ");
  Serial.println(humidity);

  Serial.print("-------------------------");
  
  // Print tE referring to temperature
  for (int i=0; i < 300;i++){
   showDigit(D1, letters[0]);
   showDigit(D2, letters[1]);
  }

  for (int i = 0; i < 300; i++) {
    if (hundreds > 0) {
      showDigit(D1, digitCode[hundreds]);
    }

    showDigit(D2, digitCode[tens] | 0b10000000); // decimal point on
    showDigit(D3, digitCode[ones]);
    showDigit(D4, 0b00000000); // blank
  }

  delay(1000);

  // Print HU referring to Humidity
  for (int i=0; i < 300;i++){
   showDigit(D1, letters[2]);
   showDigit(D2, letters[3]);
 }

  for (int i = 0; i < 300; i++) {
    showDigit(D1, 0b00000000);
    showDigit(D2, 0b00000000); // decimal point on
    showDigit(D3, digitCode[humd_tens]);
    showDigit(D4, digitCode[humd_ones]); // blank
  }

  delay(1000);

}
