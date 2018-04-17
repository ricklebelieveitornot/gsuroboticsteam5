const int centerTrigPin = 47;
const int centerEchoPin = 49;

const int leftTrigPin = 43;
const int leftEchoPin = 45;

const int rightTrigPin = 51;
const int rightEchoPin = 53;

long duration;
long duration1;
long duration2;
int Cdistance;
int Ldistance;
int Rdistance;

/*int array[1];
int x;
int y;

int getY(){
  return y;
}
int getX(){
  return x;
}*/
int getRdistance(){
  return Rdistance;
}
void sonarSetup(){
  pinMode(centerTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(centerEchoPin, INPUT); // Sets the echoPin as an Input
  pinMode(leftTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(leftEchoPin, INPUT); // Sets the echoPin as an Input
  pinMode(rightTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(rightEchoPin, INPUT); // Sets the echoPin as an Input
}

void sonarLoop(){
  //int counter = 1;
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
  //if (counter == 1){
      //x = Rdistance;
      //++counter;
      //Serial.println(array[0]);
  //}
  
  
}
