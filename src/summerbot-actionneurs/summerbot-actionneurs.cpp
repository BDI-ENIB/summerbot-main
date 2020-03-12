#include <Servo.h>
#include "summerbot-actionneurs.hpp"

/*
How to use :
Servo* myservo = initialiseDrapeau();
baisserDrapeau(myservo);
delay(1000);
leverDrapeau(myservo);
*/


Servo*
initialiseDrapeau(void) {
  Servo* myservo;
  myservo = new Servo();
  myservo->attach(SERVO7);
  return myservo;
}

void baisserDrapeau(Servo* myservo) {
  myservo->write(175);
}


void leverDrapeau(Servo* myservo) {
  myservo->write(5);//rotation de 180°
}
