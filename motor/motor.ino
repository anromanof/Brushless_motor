// program to run brushless motor

// pins
#define AIN1 0               // H-bridge A, input pin 1
#define AIN2 1               // H-bridge A, input pin 2
#define BIN2 2               // H-bridge B, input pin 1
#define BIN1 3               // H-bridge B, input pin 2
#define hallA A0             // Hall A input pin
#define hallB A1             // Hall B input pin
#define threshold 140        // Hall sensor is near north pole if value > threshold

// global variables
int sendN = 0;               // number of samples to send
int hallBv,hallAv;           // Hall values
IntervalTimer myTimer;       // data structure for plotting timer

void setup(){
  analogReadResolution(8);   // set A/D for 8 bit resolution
  pinMode(AIN1,OUTPUT);      // set H-bridge control pins as Teensy outputs
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  myTimer.begin(plotit,100); // plotit should run every 100 microseconds
}

void plotit(){
  if(sendN>0){
    Serial.print(hallAv);
    Serial.print(' ');
    Serial.println(hallBv);
    sendN -= 1;
  }
}

void off_on(int sensor,int pin1,int pin2){
  if(sensor<threshold){
    digitalWrite(pin2,HIGH);     // turn first control pin off
    digitalWrite(pin1,LOW);    // then turn second control pin on
  }else{
    digitalWrite(pin1,HIGH);     // turn first control pin off
    digitalWrite(pin2,LOW);    // then turn second control pin on
  }
}

void loop() {
  hallAv = analogRead(hallA);
  hallBv = analogRead(hallB);
  off_on(hallAv, AIN1, AIN2);
  off_on(hallBv, BIN2, BIN1);
}

void serialEvent(){
  while(Serial.available()) {
    if((char)Serial.read() == '\n') sendN = 512;
  }
}
