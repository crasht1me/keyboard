const byte NUM_ROWS = 4;
const byte NUM_COLS = 12;

byte row_pins[NUM_ROWS] = {A0, A1, A2, A3};
byte col_pins[NUM_COLS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15};


void setup() {
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  for (byte col = 0; col < NUM_COLS; col++) {
    pinMode(col_pins[col], INPUT_PULLUP);  
  }

  for (byte row = 0; row < NUM_ROWS; row++) {
    pinMode(row_pins[row], OUTPUT);
    digitalWrite(row_pins[row], LOW);

    for (byte col = 0; col < NUM_COLS; col++) {
      // reading low at the column means key is pressed
      bool is_pressed = !digitalRead(col_pins[col]);
      if (is_pressed) {
        Serial.println("pressed: R" + String(row) + " C" + String(col));
      }
    }
    // return the row to high
    digitalWrite(row_pins[row], HIGH);
    // stop treating as output
    pinMode(row_pins[row], INPUT);
  }
}
