#include <Keyboard.h>

// symbols
#define K_SPC 0x20 //space
#define K_DQO 0x22 //"
#define K_SQO 0x27 //'
#define K_OPR 0x28 //(
#define K_CPR 0x29 //)
#define K_CMA 0x2C //,
#define K_MIN 0x2D //-
#define K_DOT 0x2E
#define K_FSL 0x2F //forward slash
#define K_SCL 0x3B //;
#define K_EQU 0x3D //=
#define K_OSB 0x5B //[
#define K_CSB 0x5D //]
#define K_BSL 0x5C //backslash
#define K_OCB 0x7B //{
#define K_CCB 0x7D //}
#define K_BTK 0x60 //`backtick

// letters
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

// digits
#define KEY_0 0x30
#define KEY_1 0x31
#define KEY_2 0x32
#define KEY_3 0x33
#define KEY_4 0x34
#define KEY_5 0x35
#define KEY_6 0x36
#define KEY_7 0x37
#define KEY_8 0x38
#define KEY_9 0x39

// modifiers
#define K_C_L 0x80
#define K_S_L 0x81
#define K_A_L 0x82
#define K_G_L 0x83
#define K_C_R 0x84
#define K_S_R 0x85
#define K_A_R 0x86
#define K_G_R 0x87

// non-printable
#define K_ETR 0xB0 //enter
#define K_ESC 0xB1
#define K_BKS 0xB2 //backspace
#define K_TAB 0xB3
#define K_RHT 0xD7 //right arrow
#define K_LFT 0xD8 //left arrow
#define K_DWN 0xD9 //down arrow
#define K_AUP 0xDA //up arrow
#define K_CPS 0xC1 //caps lock
#define K_INS 0xD1 //insert
#define K_DEL 0xD4 //delete
#define K_HOM 0xD2 //home
#define K_END 0xD5
#define K_PUP 0xD3 //page up
#define K_PDN 0xD6 //page down
#define K_F04 0xC5
#define K_F05 0xC6
#define K_F06 0xC7

// meta
#define K_NON 0x00
#define FIRST_META_KEY 0xF0
#define CTALD 0xF1 //Ctrl Alt Delete
#define HIGHR 0xFF

#define DEBOUNCE_DELAY 17

const byte NUM_ROWS = 4;
const byte NUM_COLS = 12;
const byte NUM_LAYOUT_LEVELS = 2;
byte layout_level = 0;

byte row_pins[NUM_ROWS] = {A3, A2, A1, A0};
byte col_pins[NUM_COLS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15};

byte layout[NUM_LAYOUT_LEVELS][NUM_ROWS][NUM_COLS] = {
  {
    {K_TAB, KEY_Q, KEY_W, KEY_F, KEY_P, KEY_B, KEY_J, KEY_L, KEY_U, KEY_Y, K_MIN, K_BKS},
    {K_ESC, KEY_A, KEY_R, KEY_S, KEY_T, KEY_G, KEY_K, KEY_N, KEY_E, KEY_I, KEY_O, K_ETR},
    {K_S_L, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_D, KEY_M, KEY_H, K_CMA, K_DOT, K_DQO, K_S_R},
    {K_C_L, K_CSB, K_G_L, K_A_L, HIGHR, K_SPC, K_SCL, K_OCB, K_OPR, K_OSB, K_EQU, K_FSL}
  },
  {
    {K_BTK, K_INS, K_DEL, K_HOM, K_END, K_PUP, K_PDN, KEY_7, KEY_8, KEY_9, K_BSL, K_BKS},
    {K_ESC, K_BTK, K_F04, K_F05, K_F06, K_NON, K_NON, KEY_4, KEY_5, KEY_6, K_SQO, K_ETR},
    {K_S_L, K_NON, K_NON, K_NON, K_NON, K_NON, K_NON, KEY_1, KEY_2, KEY_3, K_AUP, K_S_R},
    {K_C_L, K_NON, K_G_L, K_A_L, HIGHR, K_SPC, CTALD, K_CPS, KEY_0, K_LFT, K_DWN, K_RHT}
  }
};

bool pressed_switches[NUM_ROWS][NUM_COLS] = {
  {false, false, false, false, false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false}
};

bool key_states[NUM_ROWS][NUM_COLS] = {
  {false, false, false, false, false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false}
};

void setup() {
  Keyboard.begin();
}

void loop() {
  scan_switches();
  process_keys();
  delay(DEBOUNCE_DELAY);
}

void scan_switches() {
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
      pressed_switches[row][col] = is_pressed;
    }
    // return the row to high
    digitalWrite(row_pins[row], HIGH);
    // stop treating as output
    pinMode(row_pins[row], INPUT);
  }
}

void process_keys() {
  for (byte row = 0; row < NUM_ROWS; row++) {
    for (byte col = 0; col < NUM_COLS; col++) {
      bool is_pressed_state = pressed_switches[row][col];
      if (is_pressed_state) {
        if (!key_states[row][col]) {
          press_key(row, col);
        }
      } else {
        if (key_states[row][col]) {
          release_key(row, col);
        }
      }
    }
  }
}

void press_key(byte row, byte col) {
  key_states[row][col] = true;
  bool is_normal_key = get_layout_code(row, col) < FIRST_META_KEY;
  if (is_normal_key) {
    Keyboard.press(get_layout_code(row, col));
  } else {
    switch (get_layout_code(row, col)) {
      case HIGHR:
        Keyboard.releaseAll();
        layout_level = 1;
        break;
      case CTALD:
        Keyboard.press(K_C_L);
        Keyboard.press(K_A_L);
        Keyboard.press(K_DEL);
        break;
      default:
        break;
    }
  }
}

void release_key(byte row, byte col) {
  key_states[row][col] = false;
  bool is_normal_key = get_layout_code(row, col) < FIRST_META_KEY;
  if (is_normal_key) {
    Keyboard.release(get_layout_code(row, col));
  } else {
    switch (get_layout_code(row, col)) {
      case HIGHR:
        Keyboard.releaseAll();
        layout_level = 0;
        break;
       case CTALD:
        Keyboard.releaseAll();
        break;
      default:
        break;
    }
  }
}

/*
 * Get the keycode from the layout array for the current level.
 */
byte get_layout_code(byte row, byte col) {
  return layout[layout_level][row][col];
}
