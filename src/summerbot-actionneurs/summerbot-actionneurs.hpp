#ifndef SUMMERBOTACTIONNEURS_HPP
#define SUMMERBOTACTIONNEURS_HPP

#include "../../pinout.h"

Servo*
initialiseDrapeau(void);

void
baisserDrapeau(Servo* myservo);

void
leverDrapeau(Servo* myservo);

#endif
