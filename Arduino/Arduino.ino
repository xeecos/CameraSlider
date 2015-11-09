#include <MeOrion.h>
MeStepper stp(PORT_1);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  stp.setMaxSpeed(10000);
  stp.setAcceleration(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  stp.runSpeed();
}

void setSpeed(float spd){
  stp.setSpeed(spd);
}

