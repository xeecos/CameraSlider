#include <MeOrion.h>
MeStepper stp(PORT_1);
MePort port(PORT_3);
Me7SegmentDisplay disp(PORT_4);
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  stp.setMaxSpeed(10000);
  stp.setAcceleration(1000);
}
String buffer = "";
float targetSpeed = 0;
int state = 0;
float currentSpeed = 0;
float dir = 1;
void loop() {
  while(Serial.available()){
    char c = Serial.read();
    if(c=='\n'){
      if(buffer.indexOf("forward ")>-1){
        state = 1;
        targetSpeed = buffer.substring(buffer.indexOf(" ")).toInt();
      }else if(buffer.indexOf("backward ")>-1){
        state = 2;
        targetSpeed = buffer.substring(buffer.indexOf(" ")).toInt();
      }else if(buffer.indexOf("stop")>-1){
        targetSpeed = 0;
        state = 0;
      }
      //disp.display(targetSpeed);
      buffer = "";
    }else{
      buffer+=c;
    }
  }
  if(state==2){
    if(port.dpRead2()==1){
      targetSpeed = 0;
      currentSpeed = 0;
    }
    if(currentSpeed>targetSpeed*80){
      currentSpeed -= dir;
    }
    if(currentSpeed<targetSpeed*80){
      currentSpeed += dir;
    }
    stp.setSpeed(currentSpeed);
  }
  if(state==1){
    if(port.dpRead1()==1){
      targetSpeed = 0;
      currentSpeed = 0;
    }
    if(currentSpeed>-targetSpeed*80){
      currentSpeed -= dir;
    }
    if(currentSpeed<-targetSpeed*80){
      currentSpeed += dir;
    }
    stp.setSpeed(currentSpeed);
  }
  if(state==0){
    targetSpeed = 0;
    if(currentSpeed>0){
      currentSpeed -= dir;
    }
    if(currentSpeed<0){
      currentSpeed += dir;
    }
    stp.setSpeed(currentSpeed);
  }
  if(abs(currentSpeed)>2){
    stp.runSpeed();
  }
}

void setSpeed(float spd){
  stp.setSpeed(spd);
}

