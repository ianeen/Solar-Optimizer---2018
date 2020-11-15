#include <Servo.h>

int pos = 0;
int pos2 = 0;
int bestPos = 0;
int bestPos2 = 0;
int photoPin1 = 3;
int photoPin2 = 0;
int photoPin3 = 1;
int photoPin4 = 2;
double best = 0;
double moves = 0;
boolean flip = false;

Servo servo_9;
Servo servo_10;

void setup()
{
  best = (photoPin1 + photoPin2 + photoPin3 + photoPin4);
  Serial.begin(9600);
}

void loop()
{
  servo_9.attach(9);
  servo_9.write(10);
  servo_10.attach(10);
  servo_10.write(45);
  for (pos = 10; pos <= 170; pos ++) {
    servo_9.write(pos);
    moves = (analogRead(photoPin1) + analogRead(photoPin2) + analogRead(photoPin3) + analogRead(photoPin4));
    Serial.println(moves);
    if(moves >= best)
    {
      best = moves;
      bestPos = pos;
      flip = false;
    }
    delay(100);
  }
  servo_10.write(135);
  for (pos = 170; pos >= 10; pos --) {
    servo_9.write(pos);
    moves = (analogRead(photoPin1) + analogRead(photoPin2) + analogRead(photoPin3) + analogRead(photoPin4));
    Serial.println(moves);
    if(moves >= best)
    {
      best = moves;
      bestPos = pos;
      flip = true;
    }
    delay(100);
  }
  if(!flip)
  {
    for (pos2 = 45; pos2 <= 90; pos2 ++) {
      servo_10.write(pos2);
      moves = (analogRead(photoPin1) + analogRead(photoPin2) + analogRead(photoPin3) + analogRead(photoPin4));
      if(moves >= best)
      {
        best = moves;
        bestPos2 = pos2;
      }
      delay(100);
    }
  }
  if(flip)
  {
    for (pos2 = 135; pos2 >= 90; pos2 --) {
      servo_10.write(pos2);
      moves = (analogRead(photoPin1) + analogRead(photoPin2) + analogRead(photoPin3) + analogRead(photoPin4));
      if(moves >= best)
      {
        best = moves;
        bestPos2 = pos2;
      }
      delay(100);
    }
  }
  servo_10.write(bestPos2);
  servo_10.detach();
  servo_9.detach();
  delay(20000);
}
