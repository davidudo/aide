#include <AFMotor.h>

AF_DCMotor setupDoorLock(int pin) {
  AF_DCMotor solenoidDoorLock(pin);
  solenoidDoorLock.setSpeed(200);
  solenoidDoorLock.run(RELEASE);
  return solenoidDoorLock;
}

void loopDoorLock(AF_DCMotor solenoidDoorLock) {
  solenoidDoorLock.run(FORWARD);
  solenoidDoorLock.setSpeed(255);
}

void setup() {
  AF_DCMotor solenoidDoorLock = setupDoorLock(3);
}

void loop() {
  loopDoorLock(solenoidDoorLock);
}
