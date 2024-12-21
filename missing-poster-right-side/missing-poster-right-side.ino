// the setup function runs once when you press reset or power the board
#include <Adafruit_CircuitPlayground.h>
// Switch states
const int ON = 1;
const int OFF = 0;
String isOn = "on";
String isOff = "off";

// Initialize LED variables 3, 6, 9 & 10
int yellow1 = 10;
int red1 = 1;
int pink = 0;
int blue = 9;
int green = 6;
int yellow2 = 2;
int red2 = 3;

int lightString[] = {yellow1, red1, pink, blue, green, yellow2, red2};

// initialize RGB colors as an array to match the LEDs
int rgbLightString[10][3] = {
  {200, 200, 0},
  {200, 0, 0},
  {200, 150, 150},
  {0, 0, 200},
  {0, 200, 0},
  {200, 200, 0},
  {200, 0, 0},
  {200, 150, 150},
  {0, 0, 200},
  {0, 200, 0}
};
int r;
int g;
int b;

// Initialize buttons
int leftBtn = 4;
int leftBtnState = 0;
int currentLeftState = 0;
int previousLeftState = 0;

int rightBtn = 19;
int rightBtnState = 0;
int currentRightState = 0;
int previousRightState = 0;

int pauseAmount = 10;

void setup() {
  // put your setup code here, to run once:
  for (int light : lightString) {
    pinMode(light, OUTPUT);
  }

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
    rightToLeft();
  }
  else if (currentLeftState == ON && currentRightState == OFF) {
    cycleEyes();
  }
  else if (currentLeftState == OFF && currentRightState == ON) {
    cycleEyes();
  }
  else {
    for (int i=0; i<10; i++) {
      CircuitPlayground.setPixelColor(i, 0, 0, 0);
    }
  }
  loopDeDoo();
  rightToLeft();
  leftToRight();
//  pulse();
}

void rightToLeft() {
  int steps = 20;
  for (int i = 0; i < 7; i++) {
    analogWrite(lightString[i], 255);
    delay(100);
    analogWrite(lightString[i], 0);
  }
}
void leftToRight() {
  int steps = 20;
  for (int i = 6; i >= 0; i--) {
    analogWrite(lightString[i], 255);
    delay(100);
    analogWrite(lightString[i], 0);
  }
}

void loopDeDoo() {
  
  for (int i=0; i<10; i++) {
    r = rgbLightString[i][0];
    g = rgbLightString[i][1];
    g = rgbLightString[i][2];
    CircuitPlayground.setPixelColor(i, r, g, b);
    delay(40);
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
    delay(40);
  }

  for (int i=9; i > -1; i--) {
    r = rgbLightString[i][0];
    g = rgbLightString[i][1];
    g = rgbLightString[i][2];
    CircuitPlayground.setPixelColor(i, r, g, b);
    delay(40);
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
    delay(40);
  }
}
void cycleEyes() {
  for (int r=0; r<256; r+=64) {
    for (int g=0; g<256; g+=64) {
      for(int b=0; b<256; b+=64) {
        for (int np = 0; np < 10; np++) {
          CircuitPlayground.setPixelColor(np, r, g, b);
          
        }
      }
      delay(100);
    }
  }
}
