#include<Wire.h>
#include<math.h>
#define CONVERSIONG 3.9
#include <DualVNH5019MotorShield.h>

DualVNH5019MotorShield md;

// defines pins number
const int centerTrigPin = 47;
const int centerEchoPin = 49;
const int leftTrigPin = 43;
const int leftEchoPin = 45;
const int rightTrigPin = 51;
const int rightEchoPin = 53;
const int MPU_addr=0x68;  // I2C address of the MPU-6050

//defines speed of motor
const int sped = 75;
int[3] startarray;
// defines variables
long duration;
long duration1;
long duration2;
int Cdistance;
int Ldistance;
int Rdistance;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
double accelerationX,accelerationY,accelerationZ;
double pitch,roll,yaw; //pitch y, roll z, yaw x

void setup() {
  pinMode(centerTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(centerEchoPin, INPUT); // Sets the echoPin as an Input
  pinMode(leftTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(leftEchoPin, INPUT); // Sets the echoPin as an Input
  pinMode(rightTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(rightEchoPin, INPUT); // Sets the echoPin as an Input
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600); // Starts the serial communication
  md.init();
}
void loop() {
  
  Label1:
  
  // MPU //
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  accelerationX = (int16_t)(AcX * CONVERSIONG);
  accelerationY = (int16_t)(AcY * CONVERSIONG);
  accelerationZ = (int16_t)(AcZ * CONVERSIONG);
  pitch = 180 * atan (accelerationX/sqrt(accelerationY*accelerationY + accelerationZ*accelerationZ))/M_PI;
  roll = 180 * atan (accelerationY/sqrt(accelerationX*accelerationX + accelerationZ*accelerationZ))/M_PI;
  yaw = 180 * atan (accelerationZ/sqrt(accelerationX*accelerationX + accelerationZ*accelerationZ))/M_PI;

  // Sonars //
  // Clears the trigPin
  digitalWrite(centerTrigPin, LOW);
  //delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(centerTrigPin, HIGH);
  //delayMicroseconds(10);
  digitalWrite(centerTrigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(centerEchoPin, HIGH);
  // Calculating the distance
  Cdistance= duration*0.034/2;
  // Clears the trigPin
  digitalWrite(leftTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(leftTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(leftTrigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(leftEchoPin, HIGH);
  // Calculating the distance
  Ldistance= duration1*0.034/2;
  // Clears the trigPin
  digitalWrite(rightTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(rightTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(rightTrigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(rightEchoPin, HIGH);
  // Calculating the distance
  Rdistance= duration2*0.034/2;
  
  startarray[0] = 
  // Motors //
  md.setSpeeds(-sped, sped);
  if(Cdistance <= 15 || Ldistance <= 15 || Rdistance <= 15)
  {
    md.setBrakes(0,0);
    delay(1000);
    md.setSpeeds(sped, -sped);
    delay(2000);
    if(Ldistance > Rdistance)
    { 
     md.setSpeeds(sped, sped);
     delay(1000);
     goto Label1;
    }
   else
   {
     md.setSpeeds(-sped,-sped);
     delay(1000);
     goto Label1;
   }
  }
  }
