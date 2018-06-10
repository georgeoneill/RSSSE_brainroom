#include <Adafruit_NeoPixel.h>
#define PIN 6

uint32_t color = 0;
const int id_length = 1;
const int color_length = 3;
char iI[id_length + 1];
char iR[color_length + 1];
char iG[color_length + 1];
char iB[color_length + 1];
int id = 0;
int R = 0;
int G = 0;
int B = 0;
int n = 8;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(n, PIN, NEO_GRB + NEO_KHZ400);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
  Serial.println("Neopixels: Ready");
  strip.begin();
  strip.setBrightness(255);
  strip.show();
}

void serialEvent(){

  while (Serial.available()){
    byte size = Serial.readBytes(iI, id_length);
    iI[size] = 0;
    size = Serial.readBytes(iR, color_length);
    iR[size] = 0;
    size = Serial.readBytes(iG, color_length);
    iG[size] = 0;
    size = Serial.readBytes(iB, color_length);
    iB[size] = 0;
  }

  id = atoi(iI);
  R = atoi(iR);
  G = atoi(iG);
  B = atoi(iB);
  
  if ((id) > 0){
//    strip.setPixelColor(id-1, R, G, B);

      strip.setPixelColor(id-1, R, G, B);

  } else {
      for (int i = 0; i < n; i++){
        strip.setPixelColor(i, R, G, B);
      }
  }

  strip.show();
}

//void loop() {
//  // put your main code here, to run repeatedly:
//  R = random(0,255);
//  G = random(0,255);
//  B = random(0,255);
//  for (int i = 0; i < 3; i++){
//    strip.setPixelColor(i, R, G, B);
//  }
//  strip.show();
//  delay(100);
//}

void loop() {
}


