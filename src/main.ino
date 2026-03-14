#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11

#define DATA 8
#define CLOCK 9
#define LATCH 10

#define D1 2
#define D2 3
#define D3 4
#define D4 5

DHT dht_sensor(DHTPIN, DHTTYPE);

// Q0->A, Q1->B, Q2->C, Q3->D, Q4->E, Q5->F, Q6->G, Q7->DP
byte digitCode[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

byte letters[4] = {
   0b01111000, //t
   0b01111001,//E
   0b01110110, //H
   0b00111110, //U
};

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

void sendToShiftRegister(byte value) {
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, value);
  digitalWrite(LATCH, HIGH);
}

void allDigitsOff() {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
}

void showDigit(int digitPin, byte pattern, int delayMs = 3) {
  allDigitsOff();
  sendToShiftRegister(pattern);
  digitalWrite(digitPin, LOW);   // active LOW
  delay(delayMs);
  digitalWrite(digitPin, HIGH);  // turn it back off
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
