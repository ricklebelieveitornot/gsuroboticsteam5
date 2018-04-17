// MAIN FILE
#include <math.h>

int X;
int Y;
int i;
double width;
double angle;
double initPos[3];
double currentPos[3];
void setup() {
  sonarSetup();
  motorSetup();
  mpuSetup();
  Serial.begin(9600); //Start the serial communication
  initPosi();
  initPos[0] = getPosX();
  initPos[1] = getPosY();
  initPos[2] = getPosZ();
  Serial.println("Initial Position: ");
    for(int i = 0; i<=2; i++){
     Serial.print(initPos[i]);
     Serial.print(" ");
    }
    Serial.println("");
}

void currentPosi(){
  currentPos[0] = getPosX1() - initPos[0];
  currentPos[1] = getPosY1() - initPos[1];
  currentPos[2] = getPosZ1() - initPos[2];
}

void loop() {
    sonarLoop();
    mpuLoop();
    //motorLoop();
    //X = getX();
    //if(X < getRdistance() -50){
      //Start calc angle
      //if(Y > getRdistance() +50){
        //width = sqrt(X*X + Y*Y - 2*X*Y*cos(60)); //doesnt work
      //}
    //}
    currentPosi();
    Serial.println("Current Positional Displacement: ");
    for(int i = 0; i<=2; i++){
     Serial.print(currentPos[i]);
     Serial.print(" ");
    }
    Serial.println("");
}


