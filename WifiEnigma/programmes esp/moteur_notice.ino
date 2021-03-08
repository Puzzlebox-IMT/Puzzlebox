
// Include the Arduino Stepper.h library:
#include <Stepper.h>

// Define number of steps per rotation:
const int stepsPerRevolution = 2048;

// Wiring:
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver
// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper = Stepper(stepsPerRevolution, 18,16, 5, 17);

void setup() {
  // Set the speed :
  myStepper.setSpeed(10);
}

void eject(){
  myStepper.step(stepsPerRevolution);  
  myStepper.step(stepsPerRevolution);    
  myStepper.step(stepsPerRevolution); 
  myStepper.step(stepsPerRevolution);  
  myStepper.step(stepsPerRevolution);     
}

void retract(){
  myStepper.step(-stepsPerRevolution);
  myStepper.step(-stepsPerRevolution); 
  myStepper.step(-stepsPerRevolution); 
  myStepper.step(-stepsPerRevolution); 
  myStepper.step(-stepsPerRevolution);
}
void loop() {
  eject();
  delay(2000);
  retract();
  delay(2000);
}
