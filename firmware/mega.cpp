#include <AFMotor.h>
#include <ArduinoJson.h>

AF_DCMotor leftMotor(1); // Set up motor on channel 1
AF_DCMotor rightMotor(2); // Set up motor on channel 2
AF_DCMotor solenoidDoorLock(3); // Set up the door lock

// Setup Pins
const int irPin = 45;
// const int pirPin = 37;
const int buzzerPin = 44;
const int TRIG_PINS[] = {49, 53, 48, 52};
const int ECHO_PINS[] = {47, 51, 46, 50};

bool buzzerState = false; // Initialize the buzzer state to off

const float SPEED_OF_SOUND = 0.034; // cm/us
const unsigned long DELAY_BETWEEN_READINGS = 500; // ms

// Variables for the sonar sensors
unsigned long previousMillis = 0;

// Function prototypes
// volatile int pirSensorValue = LOW;

void setup() {
  // Set up the serial ports
  Serial.begin(115200);
  Serial3.begin(115200);

  // Set up the sonar sensors
  for (int i = 0; i < 4; i++) {
    pinMode(TRIG_PINS[i], OUTPUT);
    pinMode(ECHO_PINS[i], INPUT);
  }

  // Set up the motors
  leftMotor.setSpeed(200); // Set initial motor speed to full
  rightMotor.setSpeed(200); // Set initial motor speed to full

  // Set up the door lock
  solenoidDoorLock.setSpeed(200);

  // Set the buzzer pin as an output
  pinMode(buzzerPin, OUTPUT);

  // Set up the IR sensor
  pinMode(irPin, INPUT);

  // Set up the PIR sensor
  // pinMode(pirPin, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(pirPin), PIRSensor, CHANGE);
}

void loop() {
  // get the current time
  // unsigned long currentDataMillis = millis();

  //   // Send robot information and sensor values to web server
  //   sendJsonData(Serial3, "temperature", random(0, 100));
  // }


  // Play a tone only when the buzzer is on
  if (buzzerState) {
    playSound(440, 500);
  }

  bool stopped = false;

  // if (pirSensorValue == HIGH) {
  //   Serial.println("Motion detected!");
  // }

  // Read the sonar sensors
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= DELAY_BETWEEN_READINGS) {
    previousMillis = currentMillis;
    for (int i = 0; i < 4; i++) {
      float distance = readDistance(TRIG_PINS[i], ECHO_PINS[i]);
      // Serial.print("Sensor ");
      // Serial.print(i + 1);
      // Serial.print(": ");
      // Serial.print(distance);
      // Serial.println(" cm");

      if (distance > 0 && distance <= 20 && !stopped)
      {
        stop();
        Serial.println("Stopping");
        // sendJsonData(Serial3, "sonar", "obstacle detected");
        // stopped = true;
      }
    }
  }

  int sensorStatus = digitalRead(irPin); // Set the GPIO as Input
  // int analogueSensorRead = analogueRead(irPin);

  if (sensorStatus == 1) // Check if the pin high or not
  {
    buzzerState = true;
  } else {
    buzzerState = false;
  }

  if (Serial3.available() > 0) {
    char command = Serial3.read();

    switch (command) {
      case 'F':
        Serial.println("Moving forward");
        forward();
        break;
      case 'S':
        Serial.println("Stopping");
        stop();
        break;
      case 'B':
        Serial.println("Moving backward");
        backward();
        break;
      case 'L':
        Serial.println("Turning left");
        left();
        break;
      case 'R':
        Serial.println("Turning right");
        right();
        break;
      case 'Q':
        Serial.println("Buzzer On");
        buzzerState = true;
        break;
      case 'W':
        Serial.println("Buzzer Off");
        buzzerState = false;
        break;
      case 'E':
        Serial.println("Door Unlock");
        solenoidDoorLock.setSpeed(255);
        solenoidDoorLock.run(FORWARD);
        delay(8000);
        break;
      case 'T':
        Serial.println("Lock Door");
        solenoidDoorLock.run(RELEASE);
        break;
      case 'Y':
        Serial.println("Auto Forward");
        forward();
        break;
    }
  }
}

void forward() {
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
}

void backward() {
  leftMotor.run(BACKWARD);
  rightMotor.run(BACKWARD);
}

void left() {
  leftMotor.run(BACKWARD);
  rightMotor.run(FORWARD);
}

void right() {
  leftMotor.run(FORWARD);
  rightMotor.run(BACKWARD);
}

void stop() {
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
}

void playSound(int frequency, int duration) {
  if (buzzerState) {
    // Only play the sound if the buzzer is on
    tone(buzzerPin, frequency, duration);
    delay(1000);
    noTone(buzzerPin);
  }
}

float readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH, 10000); // Timeout after 10ms
  float distance = duration * SPEED_OF_SOUND / 2;
  return distance;
}

void PIRSensor() {
  // pirSensorValue = digitalRead(pirPin);
}

void sendJsonData(Stream& stream, const char* sensor, int value) {
  // Create a JSON object and serialize it
  StaticJsonDocument<256> doc;
  doc["sensor_name"] = sensor;
  doc["value"] = value;
  char jsonStr[256];
  serializeJson(doc, jsonStr);

  // Send the JSON data to the serial port
  stream.println(jsonStr);
}

