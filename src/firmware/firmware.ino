#define KEY_A 0x04
#define KEY_B 0x05
#define KEY_C 0x06
#define KEY_D 0x07
#define KEY_E 0x08
#define KEY_F 0x09
#define KEY_G 0x0A
#define KEY_H 0x0B
#define KEY_I 0x0C
#define KEY_J 0x0D
#define KEY_K 0x0E
#define KEY_L 0x0F
#define KEY_SHIFT_L 0x81

const byte NUM_ROWS = 4;
const byte NUM_COLS = 2;

byte row_pins[NUM_ROWS] = {A0, A1, A2, A3};
byte col_pins[NUM_COLS] = {2, 3/*, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15*/};

byte layout[NUM_ROWS][NUM_COLS] = {
  {KEY_A, KEY_B},
  {KEY_C, KEY_D},
  {KEY_E, KEY_F},
  {KEY_G, KEY_H}
};


void setup() {
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  // reinitialise the column pins to allow sharing with other hardware
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
        //Serial.println("pressed: R" + String(row) + " C" + String(col));
        Serial.println("pressed keycode: " + String(layout[row][col]));
      }
    }
    // return the row to high
    digitalWrite(row_pins[row], HIGH);
    // stop treating as output
    pinMode(row_pins[row], INPUT);
  }
}
