#include <Encoder.h>
#include <PID_v1.h> // Add PID library
Encoder myEnc(5,6);
int STBY = 10; //standby

//Motor A
int PWMA = 3; //Speed control
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

double Setpoint, Input, Output;
//PID gain parameters
double Kp1=0.5, Ki1=0.6, Kd1=0.075;
PID myPID1(&Input, &Output, &Setpoint, Kp1, Ki1, Kd1, DIRECT);

void setup(){
  Serial.begin(9600);
  float Input1  = 0;
   Setpoint = 200; // Desired RPM values
   myPID1.SetMode(AUTOMATIC);
   
pinMode(STBY, OUTPUT);

pinMode(PWMA, OUTPUT);
pinMode(AIN1, OUTPUT);
pinMode(AIN2, OUTPUT);

Serial.println("Basic Encoder Test:");
}
long oldPosition  = -999;
float start;
float stop_=0;
float diff;
float rpm = 0;
int counter=0;
int PWM_A;
void loop(){
  start = millis();
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
       counter++;
    if(counter%2048==0){
      diff = start-stop_;
      rpm=1/(diff/60000);
      stop_=start;
  Serial.print("right :\t");Serial.print(rpm);
       Serial.println();
      }

  }
  right(rpm);
move(1, PWM_A, 1); //motor 1, full speed, left



}
void right(int input_1 )
{
  Input = input_1;
  myPID1.Compute();
  PWM_A=Output;

}
void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

digitalWrite(STBY, HIGH); //disable standby

boolean inPin1 = LOW;
boolean inPin2 = HIGH;

if(direction == 1){
inPin1 = HIGH;
inPin2 = LOW;
}

if(motor == 1){
digitalWrite(AIN1, inPin1);
digitalWrite(AIN2, inPin2);
analogWrite(PWMA, speed);
}
}

void stop(){
//enable standby
digitalWrite(STBY, LOW);
}
