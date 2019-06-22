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

#define K_SPC 0x20
#define K_DQO 0x22
#define K_FSL 0x2F
#define K_OPR 0x28 //(
#define K_CPR 0x29 //)
#define K_CMA 0x2C
#define K_DOT 0x2E
#define K_FCL 0x3A //:
#define K_SCL 0x3B //;
#define K_EQU 0x3D //=
#define K_OSB 0x5B //[
#define K_CSB 0x5D //]
#define K_USC 0x5F //_
#define K_OCB 0x7B //{
#define K_CCB 0x7D //}
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

#define K_C_L 0x80
#define K_S_L 0x81
#define K_A_L 0x82
#define K_G_L 0x83
#define K_C_R 0x84
#define K_S_R 0x85
#define K_A_R 0x86
#define K_G_R 0x87

#define K_ETR 0xB0
#define K_BKS 0xB2
#define K_TAB 0xB3
#define K_ESC 0xB1

#define LOWER 0x00
#define HIGHR 0x00

const byte NUM_ROWS = 4;
const byte NUM_COLS = 12;

byte row_pins[NUM_ROWS] = {A0, A1, A2, A3};
byte col_pins[NUM_COLS] = {2, 3, 4, 5, 6, 7, 8, 9, 15, 14, 16, 10};

byte layout[NUM_ROWS][NUM_COLS] = {
  {K_TAB, KEY_Q, KEY_W, KEY_F, KEY_P, KEY_B, KEY_J, KEY_L, KEY_U, KEY_Y, K_USC, K_BKS},
  {K_ESC, KEY_A, KEY_R, KEY_S, KEY_T, KEY_G, KEY_K, KEY_N, KEY_E, KEY_I, KEY_O, K_ETR},
  {K_S_L, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_D, KEY_M, KEY_H, K_CMA, K_DOT, K_DQO, K_S_R},
  {K_C_L, K_G_L, K_A_L, LOWER, HIGHR, K_SPC, K_OPR, K_CPR, K_OCB, K_CCB, K_FSL, K_EQU}
};

bool pressed_switches[NUM_ROWS][NUM_COLS] = {
  {false, false, false, false, false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false}
};


void setup() {
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
