// program to step through coil voltages (turning rotor slowly)

// pins
#define AIN1 0               // H-bridge A, input pin 1
#define AIN2 1               // H-bridge A, input pin 2
#define BIN1 2               // H-bridge B, input pin 1
#define BIN2 3               // H-bridge B, input pin 2
int l = 5;

void setup() {
  pinMode(AIN1,OUTPUT);      // set H-bridge control pins as Teensy outputs
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
}

void off_on(int pin1,int pin2){
  digitalWrite(pin2,LOW);     // turn first control pin off
  digitalWrite(pin1,HIGH);    // then turn second control pin on
}

void loop() {
  off_on(AIN2,AIN1);
  delay(1000);
  off_on(BIN2,BIN1);
  delay(1000);
  off_on(AIN1,AIN2);
  delay(1000);
  off_on(BIN1,BIN2);
  delay(1000);
}
