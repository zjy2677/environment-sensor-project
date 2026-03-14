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

void sendPattern(byte value) {
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, ~value); // invert for common anode
  digitalWrite(LATCH, HIGH);
}

void showSegment(byte pattern) {

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);

  sendPattern(pattern);

  digitalWrite(D1, LOW);

  delay(800);
}

void loop() {

  showSegment(0b00000001);
  showSegment(0b00000010);
  showSegment(0b00000100);
  showSegment(0b00001000);
  showSegment(0b00010000);
  showSegment(0b00100000);
  showSegment(0b01000000);
  showSegment(0b10000000);
}
