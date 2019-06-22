/*#define KEY_A 0x04
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
#define KEY_SHIFT_L 0x81 */

#include <Keyboard.h>

#define KEY_SPACE 0x20
#define KEY_BACKSPACE 0xB2
#define KEY_A 0x61
#define KEY_B 0x62
#define KEY_C 0x63
#define KEY_D 0x64
#define KEY_E 0x65
#define KEY_F 0x66
#define KEY_G 0x67
#define KEY_H 0x68
#define KEY_I 0x69
#define KEY_J 0x6A
#define KEY_K 0x6B
#define KEY_L 0x6C
#define KEY_M 0x6D
#define KEY_N 0x6E
#define KEY_O 0x6F
#define KEY_P 0x70
#define KEY_Q 0x71
#define KEY_R 0x72
#define KEY_S 0x73
#define KEY_T 0x74
#define KEY_U 0x75
#define KEY_V 0x76
#define KEY_W 0x77
#define KEY_X 0x78
#define KEY_Y 0x79
#define KEY_Z 0x7A
#define KEY_CTRL_L 0x80
#define KEY_SHIFT_L 0x81
#define KEY_ALT_L 0x82

const byte NUM_ROWS = 4;
const byte NUM_COLS = 12;

byte row_pins[NUM_ROWS] = {A0, A1, A2, A3};
byte col_pins[NUM_COLS] = {2, 3, 4, 5, 6, 7, 8, 9, 15, 14, 16, 10};

byte layout[NUM_ROWS][NUM_COLS] = {
  {KEY_A, KEY_B, KEY_A, KEY_B, KEY_A, KEY_B, KEY_A, KEY_B, KEY_A, KEY_B, KEY_A, KEY_B},
  {KEY_C, KEY_D, KEY_A, KEY_B, KEY_A, KEY_B, KEY_A, KEY_B, KEY_A, KEY_B, KEY_A, KEY_B},
  {KEY_E, KEY_F, KEY_A, KEY_B, KEY_A, KEY_B, KEY_A, KEY_B, KEY_A, KEY_B, KEY_A, KEY_B},
  {KEY_G, KEY_H, KEY_A, KEY_B, KEY_A, KEY_B, KEY_A, KEY_B, KEY_A, KEY_B, KEY_A, KEY_B}
};

bool pressed_switches[NUM_ROWS][NUM_COLS] = {
  {false, false, false, false, false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false}
};


void setup() {
  Serial.begin(9600);
  Keyboard.begin();
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
        Serial.println("pressed: R" + String(row) + " C" + String(col));
        //Serial.println("pressed keycode: " + String(layout[row][col]));

        if (!pressed_switches[row][col]) {
          pressed_switches[row][col] = true;
          Keyboard.press(layout[row][col]);
        }
      } else {
        if (pressed_switches[row][col]) {
          pressed_switches[row][col] = false;
          Keyboard.release(layout[row][col]);
        }
      }
    }
    // return the row to high
    digitalWrite(row_pins[row], HIGH);
    // stop treating as output
    pinMode(row_pins[row], INPUT);
  }
}
