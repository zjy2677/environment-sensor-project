#define DATA 8
#define CLOCK 9
#define LATCH 10

#define D1 2
#define D2 3
#define D3 4
#define D4 5

void setup() {

  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
}

void loop() {

  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, ~0b11111111); // all segments
  digitalWrite(LATCH, HIGH);

  digitalWrite(D1, LOW);  // enable digit 1

  delay(1000);
}
