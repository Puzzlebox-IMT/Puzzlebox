#include <Servo.h>

Servo servo1;
static const int servoPin = 4;

void setup() {
  servo1.attach(servoPin);
}

//met le servo sur la position 1,2,3 suivant l'avancée globale de la reprise de contrôle de la maison
void servo(int number){
  if (number == 1){
      for(int posDegrees = 180; posDegrees >= 120; posDegrees--) {
      servo1.write(posDegrees);
      delay(20);
    }
  }else if (number == 2){
      for(int posDegrees = 120; posDegrees >= 60; posDegrees--) {
      servo1.write(posDegrees);
      delay(20);
      }
  }else if (number == 3){
      for(int posDegrees = 60; posDegrees >= 0; posDegrees--) {
      servo1.write(posDegrees);
      delay(20);
      }
  }else if (number == 0){
      servo1.write(180);
  }
}


void loop() {

    servo(1);
    delay(500);
    servo(2);
    delay(500);
    servo(3);
    delay(2000);
    servo(0);
    delay(2000);
 
}
