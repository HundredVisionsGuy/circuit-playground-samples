// the setup function runs once when you press reset or power the board
#include <Adafruit_CircuitPlayground.h>
// Switch states
const int ON = 1;
const int OFF = 0;
String isOn = "on";
String isOff = "off";

// Initialize teeth variables 3, 6, 9 & 10
int upperLeftTooth = 6;
int upperRightTooth = 9;
int lowerLeftTooth = 3;
int lowerRightTooth = 10;

int teeth[] = {upperLeftTooth, upperRightTooth, lowerLeftTooth, lowerRightTooth};

// Initialize buttons
int leftBtn = 4;
int leftBtnState = 0;
int currentLeftState = 0;
int previousLeftState = 0;
int rightBtn = 19;
int rightBtnState = 0;
int currentRightState = 0;
int previousRightState = 0;

// Eyes
int leftEye = 9;
int rightEye = 6;

int pauseAmount = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(upperLeftTooth, OUTPUT);
  pinMode(upperRightTooth, OUTPUT);
  pinMode(lowerLeftTooth, OUTPUT);
  pinMode(lowerRightTooth, OUTPUT);
  pinMode(leftBtn, INPUT);
  pinMode(rightBtn, INPUT);
  Serial.begin(9600);
  CircuitPlayground.begin();
}

// the loop function runs over and over again forever
void loop() {
  // poll the buttons
  currentLeftState = digitalRead(leftBtn);
  currentRightState = digitalRead(rightBtn);
  delay(250);
  currentLeftState = digitalRead(leftBtn);
  currentRightState = digitalRead(rightBtn);

  if (currentLeftState == ON && currentRightState == ON) {
    blinketyBlink();
  }
  else if (currentLeftState == ON && currentRightState == OFF) {
    pulse();
  }
  else if (currentLeftState == OFF && currentRightState == ON) {
    cycleEyes();
  }
  else {
    CircuitPlayground.setPixelColor(6, 200, 0, 0);
    CircuitPlayground.setPixelColor(9, 200, 0, 0);
  }
  blinketyBlink();
  pulse();
  cycleEyes();
}

void pulse() {
  for (int i = 0; i <= 112; i++) {
    for (int j = 0; j < 4; j++) {
      int tooth = teeth[j];
      analogWrite(tooth, i);
      delay(5);
    }
  }
  for (int i = 112; i >= 0; i--) {
    for (int j = 0; j < 4; j++) {
      int tooth = teeth[j];
      analogWrite(tooth, i);
      delay(5);
    }
  }
}

void blinketyBlink() {
  int steps = 20;
  for (int i=0; i<steps; i++) {
    for (int j = 0; j < 4; j++) {
      int tooth = teeth[j];
      analogWrite(tooth, 255);   
      delay(i * 10);             
      analogWrite(tooth, 0);   
      delay(i * 10);    
    }       
  }
  for (int j=steps; j>0; j--) {
    for (int i = 0; i < 4; i++) {
      int tooth = teeth[i];
      digitalWrite(tooth, HIGH);   
      delay(j * 10);             
      digitalWrite(tooth, LOW);   
      delay(j * 10);
    }         
  }
}
void cycleEyes() {
  for (int r=0; r<256; r+=55) {
    for (int g=0; g<256; g+=55) {
      for(int b=0; b<256; b+=55) { 
        CircuitPlayground.setPixelColor(6, r, g, b);
        CircuitPlayground.setPixelColor(9, r, g, b);
        delay(100);
      }
    }
  }
}
