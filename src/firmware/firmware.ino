
int pin_col1 = 2;
int pin_row1 = 6;


// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  pinMode(pin_row1, INPUT_PULLUP);

  pinMode(pin_col1, OUTPUT);
  digitalWrite(pin_col1, LOW);
  if (digitalRead(pin_row1)) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }
  digitalWrite(pin_col1, HIGH);
  pinMode(pin_col1, INPUT);
}
