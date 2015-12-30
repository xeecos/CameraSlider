//#include <SoftwareSerial.h>
//SoftwareSerial sw(A3,A2);
int dirPin = 11;
int stepPin = 10;
float speed = 0;
String buffer = "";
void moveStep(boolean dir){
  digitalWrite(dirPin,dir?LOW:HIGH);
  digitalWrite(stepPin,HIGH);
  delayMicroseconds(1);
  digitalWrite(stepPin,LOW);
  delayMicroseconds(1); 
}
void runSpeed(){
  int time = 0;
  if(speed>0){
    moveStep(false);
    time = speed;
  }else if(speed<0){
    moveStep(true);
    time = -speed;
  }
  delay(time);
}
void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  //sw.begin(115200);
  Serial.begin(115200);
}
void loop() {
  if(Serial.available()){
    char c = Serial.read();
    buffer+=c;
    if(c=='\n'){
      int i = buffer.lastIndexOf("forward");
      int n = 0;
      if(i>-1){
        speed = 200.0/(1.0+buffer.substring(8,buffer.length()-1).toInt());
      }else{
        i = buffer.lastIndexOf("backward");
        if(i>-1){
          speed = -200.0/(1.0+buffer.substring(9,buffer.length()-1).toInt());
        }else{
          i = buffer.lastIndexOf("stop");
          if(i>-1){
          speed = 0;
          }
        }
      }
     buffer="";
    }
  }
  runSpeed();
}
