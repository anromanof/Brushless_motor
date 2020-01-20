// program to read two Hall-effect sensors and write results on serial port

#define HallA A0                    // analog channel for Hall A device
#define HallB A1                    // analog channel for Hall B device
int HallAv, HallBv;                 // variables to hold sensor values

void setup(){
  Serial.begin(19200);             // use serial port to show results
  analogReadResolution(8);          // set A/D converter to 8 bits (0--255)
}

void loop(){
  HallAv = analogRead(HallA);
  HallBv = analogRead(HallB);
  Serial.print(HallAv);
  Serial.print(' ');
  Serial.println(HallBv);
  delay(10);
}
