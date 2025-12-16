int trigL = 7;
int echoL = 6;
int trigF = 5;
int echoF = 4;
int trigR = 2;
int echoR = 3;
int enA = 10;
int in1 = 8;
int in2 = 11;
int enB = 9;
int in3 = 12;
int in4 = 13;
int timeF,timeR,timeL;
int F,R,L;
bool Turning = false;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(trigF,OUTPUT);
    pinMode(echoF,INPUT);
    pinMode(trigR,OUTPUT);
    pinMode(echoR,INPUT);
    pinMode(trigL,OUTPUT);
    pinMode(echoL,INPUT);
    pinMode(enA,OUTPUT);
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(enB,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);
}
void forward() {
      analogWrite(enA,170);
      digitalWrite(in1,1);
      digitalWrite(in2,0);
      analogWrite(enB,170);
      digitalWrite(in3,1);
      digitalWrite(in4,0);
}
void turnleft() {
      analogWrite(enA,255);
      digitalWrite(in1,1);
      digitalWrite(in2,0);
      analogWrite(enB,255);
      digitalWrite(in3,0);
      digitalWrite(in4,1);
}
void turnright() {
      analogWrite(enA,255);
      digitalWrite(in1,0);
      digitalWrite(in2,1);
      analogWrite(enB,255);
      digitalWrite(in3,1);
      digitalWrite(in4,0);
}
void rightfix() {
      analogWrite(enA,180);
      digitalWrite(in1,1);
      digitalWrite(in2,1);
      analogWrite(enB,255);
      digitalWrite(in3,0);
      digitalWrite(in4,1);
}
void leftfix() {
      analogWrite(enA,255);
      digitalWrite(in1,0);
      digitalWrite(in2,1);
      analogWrite(enB,160);
      digitalWrite(in3,1);
      digitalWrite(in4,1);
}
void reverse1() {
      analogWrite(enA,180);
      digitalWrite(in1,0);
      digitalWrite(in2,1);
      analogWrite(enB,160);
      digitalWrite(in3,1);
      digitalWrite(in4,0);
}
void reverse2() {
     analogWrite(enA,180);
     digitalWrite(in1,0);
     digitalWrite(in2,1);
     analogWrite(enB,120);
     digitalWrite(in3,0);
     digitalWrite(in4,1);
}
void stop() {
     analogWrite(enA,0);
     digitalWrite(in1,1);
     digitalWrite(in2,1);
     analogWrite(enB,0);
     digitalWrite(in3,1);
     digitalWrite(in4,1);
}
void TurnAround(){
  stop();
  delay(200);
  reverse2();
  delay(400);
  reverse1();
  delay(460);
  stop();
  delay(200);
  Turning = false;
}
void readSensors(){
  if (Turning == true) {
    return;
    }
  else {
  digitalWrite(trigF, 0);
  delayMicroseconds(2);
  digitalWrite(trigF, 1);//set active 10 microsec
  delayMicroseconds(10);
  digitalWrite(trigF, 0);//read frontEcho, return soundwave in microsec
  timeF = pulseIn(echoF, 1);//max calc time //calc total time 
  F = timeF *0.0342/2; //calc  to wall

  digitalWrite(trigR, 0);
  delayMicroseconds(2);
  digitalWrite(trigR, 1);//set active 10 microsec
  delayMicroseconds(10);
  digitalWrite(trigR, 0);//read frontEcho, return soundwave in microsec
  timeR = pulseIn(echoR, 1);//max calc time //calc total time 
  R = timeR *0.0342/2; //calc  to wall

  digitalWrite(trigL, 0);
  delayMicroseconds(2);
  digitalWrite(trigL, 1);//set active 10 microsec
  delayMicroseconds(10);
  digitalWrite(trigL, 0);//read frontEcho, return soundwave in microsec
  timeL = pulseIn(echoL, 1);//max calc time //calc total time 
  L = timeL *0.0342/2; //calc  to wall
  }
}
// hieu dien the roi tren 1 tai bat ki se co 1 dong dien chay qua 
void loop() {
  readSensors();
   if (L >= 20) { // turn left
      Turning = true;
      Serial.println("Rẽ trái");
      stop();
      delay(300);
      forward();
      delay(300);
      stop();
      delay(300);
      turnleft();
      delay(270);
      stop();
      delay(200);
      forward();
      delay(300);
      stop(); 
      delay(200);
      Turning = false;
   }
   else if (L < 20 && F <= 7 && R > 15) { //turn right
      Serial.println("Rẽ phải");
      Turning = true;
      stop();
      delay(200);
      turnright();
      delay(270);
      stop();
      delay(200);
      forward();
      delay(250);
      stop();
      delay(450);
      Turning = false;
    }
   else if (L <= 8 && F <= 20 && R <= 8){ //around
     Serial.print("Trường hợp đặc biệt:");
     Turning = true;
     stop();
     delay(400);
     forward();
     delay(220);
     stop();
     delay(500);
     Turning = false;
       if (L >= 20) { // turn left
          Serial.println("Rẽ trái");
          Turning = true;
          stop();
          delay(300);
          turnleft();
          delay(270);
          stop();
          delay(200);
          forward();
          delay(300);
          stop(); 
          delay(200);
          Turning = false;
        }
      
       else if (L < 20 && F >= 10){//forward
          return;
       }

       else if (L < 20 && F <= 7 && R > 15) { //turn right
        Turning = true;
        stop();
        delay(200);
        turnright();
        delay(270);
        stop();
        delay(200);
        forward();
        delay(350);
        stop();
        delay(200);
        Turning = false;
        }
       else {
          Serial.println("Quay đầu");
          Turning = true;
          TurnAround();
        }
    }
    else{
      if (L <= 2 && F > 10 && R >= 10) {//fix lệch trái
        Turning = true;
        leftfix();
        delay(250);
        stop();
        delay(200);
        forward();
        delay(350);
        stop();
        delay(200);
        rightfix();
        delay(220);
        stop();
        delay(100);
        Turning = false;
      }
      else if (R <= 2 && F > 10 && 10 < L < 20){
        Turning = true;
        rightfix();
        delay(200);
        stop();
        delay(200);
        forward();
        delay(300);
        stop();
        delay(200);
        leftfix();
        delay(150);
        stop();
        delay(200);
        Turning = false;
      }
      else{ //forward
        forward();
      }
}
}