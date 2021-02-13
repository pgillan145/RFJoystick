#include <RFduinoBLE.h>

const int LEFT_RIGHT = 2;
const int UP_DOWN = 3;
const int LED = 6;   // status light - on is connected
const int lr_center = 4;
const int ud_center = 4;

void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(LEFT_RIGHT, INPUT);  
  pinMode(UP_DOWN, INPUT);
  pinMode(LED, OUTPUT);

  // in ms (converted to 0.625ms units) - range 20ms to 10.24s - default 80ms
  RFduinoBLE.advertisementInterval = 250;
  // -20 dBm to +4 dBm - default +4 dBm
  RFduinoBLE.txPowerLevel = 0;
  RFduinoBLE.deviceName = "RFJoystick";
  RFduinoBLE.advertisementData = "joystick";
  RFduinoBLE.begin(); 
}

int last_dir = -1;
bool connected = false;
void loop() {
  if (connected) {
    long int lr = analogRead(LEFT_RIGHT);
    long int ud = analogRead(UP_DOWN);

    int dir = 0;

    if (ud > ud_center && lr == lr_center) { dir = 1; }
    else if (ud > ud_center && lr > lr_center) { dir = 2; }
    else if (ud == ud_center && lr > lr_center) { dir = 3; }
    else if (ud < ud_center && lr > lr_center) { dir = 4; }
    else if (ud < ud_center && lr == lr_center) { dir = 5; }
    else if (ud < ud_center && lr < lr_center) { dir = 6; }
    else if (ud == ud_center && lr < lr_center) { dir = 7; }
    else if (ud > ud_center && lr < lr_center) { dir = 8; }
    if (dir != last_dir) {
      Serial.print(lr);
      Serial.print("/");
      Serial.print(ud);
      Serial.print(":");
      Serial.println(dir);
      RFduinoBLE.send(dir);
      last_dir = dir;
    }
  }
}

void RFduinoBLE_onConnect() {
  //Serial.println("connected()");
  digitalWrite(6, HIGH);
  connected = true;
}
void RFduinoBLE_onDisconnect() {
  //Serial.println("disconnected()");
  digitalWrite(6, LOW);
  connected = false;
}
