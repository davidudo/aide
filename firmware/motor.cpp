#include <AFMotor.h>

AF_DCMotor rightMotor(1);
AF_DCMotor leftMotor(2);

void setup() 
{
	//Set initial speed of the motor & stop
	rightMotor.setSpeed(200);
	rightMotor.run(RELEASE);
	leftMotor.setSpeed(200);
	leftMotor.run(RELEASE);
}
void loop() 
{
	rightMotor.run(FORWARD);	
	rightMotor.setSpeed(255);
	leftMotor.run(FORWARD);	
	leftMotor.setSpeed(255);
}
