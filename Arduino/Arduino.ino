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
int speed = 0;
int state = 0;
void loop() {
  if(Serial.available()){
    char c = Serial.read();
    if(c=='\n'){
      if(buffer.indexOf("forward ")>-1){
        speed = buffer.substring(buffer.indexOf(" ")).toInt();
        stp.setSpeed(-speed*80);
        state = 1;
      }else if(buffer.indexOf("backward ")>-1){
        speed = buffer.substring(buffer.indexOf(" ")).toInt();
        stp.setSpeed(speed*80);
        state = 2;
      }else if(buffer.indexOf("stop")>-1){
        speed = 0;
        state = 0;
      }
      disp.display(speed);
      buffer = "";
    }else{
      buffer+=c;
    }
  }
  if(state==2){
    if(port.dpRead2()==1){
      speed = 0;
    }
  }
  if(state==1){
    if(port.dpRead1()==1){
      speed = 0;
    }
  }
  if(speed>0){
    stp.runSpeed();
  }
}

void setSpeed(float spd){
  stp.setSpeed(spd);
}

