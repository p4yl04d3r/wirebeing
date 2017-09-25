int incomingByte = 0;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 12); // RX, TX
#define COMMON_ANODE

int enA = 10;//right motor (robot's right)
int in1 = 9;
int in2 = 8;

int enB = 5;//left motor (robot's left)
int in3 = 7;
int in4 = 6;


int bluepin = A1; //define RGB LED pins
int redpin = A2;
int greenpin = A3;

int speed = 80; //change speed here, can range from 0 to 255.


void setup()
{

  RGB(255, 0, 255); //blue

  Serial.begin(9600); //Use serial monitor at 9600 for debugging and controlling from computer
  mySerial.begin(9600);  //Software serial for bluetooth module
  Serial.println("Motor test!");

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}


void right()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enA, speed);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enB, speed);
}

void left()
{

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enA, speed);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enB, speed);
}

void backward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enA, (speed));

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enB, (speed));
}

void forward()
{

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enA, speed);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enB, speed);
}

void stop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void RGB (int R, int G, int B) {
  #ifdef COMMON_ANODE
    R = 255 - R;
    G = 255 - G;
    B = 255 - B;
  #endif
  analogWrite(redpin, R);
  analogWrite(greenpin, G);
  analogWrite(bluepin, B);
}

void loop()
{



  if (mySerial.available() > 0) {
//    incomingByte = Serial.read();
    incomingByte = mySerial.read();
  }



  switch (incomingByte)
  {
    case 'S':
      { stop();
 //       Serial.println("Stop\n");
        incomingByte = '*';
      }

      break;

    case 'F':
      { forward();
        Serial.println("Forward\n");
        incomingByte = '*';
      }
      break;

    case 'B':
      { backward();
        Serial.println("Backward\n");
        incomingByte = '*';
      }
      break;

    case 'R':
      {
        right();
        Serial.println("Rotate Right\n");
        incomingByte = '*';
      }
      break;


    case 'L':
      {
        left();
        Serial.println("Rotate Left\n");
        incomingByte = '*';
      }
      break;

    case 'W':
      {
        RGB(255, 0, 0); //red
        Serial.println("Red Eyes on");
        incomingByte = '*';
      }
      break;

    case 'w':
      {
        RGB(0, 0, 0); //red
        Serial.println("Red Eyes off");
        incomingByte = '*';
      }
      break;

    case 'U':
      {
        RGB(0, 0, 255); //blue
        Serial.println("Blue Eyes on");
        incomingByte = '*';
      }
      break;

    case 'u':
      {
        RGB(0, 0, 0); //Blue
        Serial.println("Blue Eyes off");
        incomingByte = '*';
      }
      break;
      
    case 'V':
      {
        RGB(0, 255, 0); //green
        Serial.println("Green Eyes on");
        incomingByte = '*';
      }
      break;

       case 'v':
      {
        RGB(0, 0, 0); //green
        Serial.println("Green Eyes off");
        incomingByte = '*';
      }
      break;
  }

}
