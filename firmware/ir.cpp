// Pin for the IR sensor
int irPin = 45;

// Pin for the piezo buzzer
int buzzerPin = 44;

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  pinMode(irPin, INPUT);

  // Set the buzzer pin as an output
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int sensorStatus = digitalRead(irPin); // Set the GPIO as Input

  if (sensorStatus == 1) // Check if the pin high or not
  {
    Serial.println("Robot Compromised");
    // Ring Alarm
    playSound(440, 500);
    delay(500);
  } else {
    Serial.println("Robot Okay");
    // Do nothing
  }

  // Wait for a short time before reading again
  delay(100);
}

void playSound(int frequency, int duration) {
  tone(buzzerPin, frequency, duration);
  delay(1000);
}
