// Pin for the piezo buzzer
int buzzerPin = 44;

void setup() {
  // Set the buzzer pin as an output
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Play a unique tone for being carried from the ground
  playSound(440, 500);
  delay(500);

  // Play a unique tone for unlocking the package carriage
  playSound(880, 500);
  delay(500);

  // Play a unique tone for obstruction by a human
  playSound(1760, 500);
  delay(500);
}

void playSound(int frequency, int duration) {
  tone(buzzerPin, frequency, duration);
  delay(1000);
}
