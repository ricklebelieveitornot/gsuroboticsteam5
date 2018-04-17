#include <DualVNH5019MotorShield.h>

DualVNH5019MotorShield md;
const int sped = 70;
//int q[3];
//int p[3];
void Lrotate(){
  md.setSpeeds(sped, 0);
  delay(2000);
}

void Rrotate(){
  md.setSpeeds(0,-sped);
  delay(2000);
}

void motorSetup(){
  md.init();
}

void motorLoop(){
  /*q[0] = Rdistance - 10;
  q[1] = Rdistance;
  q[2] = Rdistance + 10;
  p[0] = Ldistance - 10;
  p[1] = Ldistance;
  p[2] = Ldistance + 10;
  
  md.setSpeeds(-sped, sped);
  for(Ldistance : q){
    md.setSpeed(-sped, sped);
    delay(1000);
  }
  for(Rdistance : p){
    md.setSpeed(-sped, sped);
    delay(1000);
  }*/
  md.setSpeeds(-sped, sped);
  if(Ldistance <= 25 && Rdistance <= 25){
    Serial.println("Larger Width!");
  }
  if(Cdistance <= 25 || Ldistance <= 25 || Rdistance <= 25)
  {
    md.setBrakes(0,0);
    delay(1000);
    if(Ldistance > Rdistance)
    { 
     Lrotate();
    }
   else
   {
     Rrotate();
  }
  }
}
