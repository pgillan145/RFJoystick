#include <RFduinoBLE.h>

const int LEFT_RIGHT = 2;
const int UP_DOWN = 3;

void setup() {
  //Serial.begin(9600);
  delay(1000);
  pinMode(LEFT_RIGHT, INPUT);  
  pinMode(UP_DOWN, INPUT);
  RFduinoBLE.deviceName = "RFJoystick";
  RFduinoBLE.advertisementData = "joystick";
  RFduinoBLE.begin(); 
}

int last_dir = -1;
void loop() {
  long int lr = analogRead(LEFT_RIGHT);
  long int ud = analogRead(UP_DOWN);
  int dir = 0;
  
  if      (ud == 4 && lr == 3) { dir = 1; }
  else if (ud == 4 && lr == 4) { dir = 2; }
  else if (ud == 3 && lr == 4) { dir = 3; }
  else if (ud == 2 && lr == 4) { dir = 4; }
  else if (ud == 2 && lr == 3) { dir = 5; }
  else if (ud == 2 && lr == 2) { dir = 6; }
  else if (ud == 3 && lr == 2) { dir = 7; }
  else if (ud == 4 && lr == 2) { dir = 8; }
  if (dir != last_dir) {
    RFduinoBLE.send(dir);
    last_dir = dir;
  }
}
