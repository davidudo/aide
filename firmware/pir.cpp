// Pin for the PIR sensor
int pirPin = 37;

unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
   Serial.begin(9600);
   pinMode(pirPin, INPUT);
}

void loop() {
   unsigned long currentMillis = millis();

   if (currentMillis - previousMillis >= interval) {
     previousMillis = currentMillis;
     PIRSensor();
   }
}

void PIRSensor() {
  int pirSensorValue = digitalRead(pirPin);
  Serial.println(pirSensorValue);
}
// Pin for the PIR sensor
int pirPin = 22;

unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
   Serial.begin(9600);
   pinMode(pirPin, INPUT);
}

void loop() {
   unsigned long currentMillis = millis();

   if (currentMillis - previousMillis >= interval) {
     previousMillis = currentMillis;
     PIRSensor();
   }
}

void PIRSensor() {
  int pirSensorValue = digitalRead(pirPin);
  Serial.println(pirSensorValue);
}
