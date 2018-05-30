#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PWMServoDriver.h>

uint16_t color = 0;
const int color_length = 3;
const int id_length = 1;
char iI[id_length + 1];
char iR[color_length + 1];
char iG[color_length + 1];
char iB[color_length + 1];
int id = 0;
uint16_t R = 0;
uint16_t G = 0;
uint16_t B = 0;
int n_bulbs = 1;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  // pwm init
  pwm.begin();
  pwm.setPWMFreq(1000);
  Wire.setClock(400000);
  // set all LEDs to off
  for (int i = 1; i < n_bulbs + 1; i++) {
    go_led(i, 0, 0, 0);
  }

  //serial init
  Serial.begin(9600);
  Serial.setTimeout(5);
  Serial.println("RSSSE Brain LEDs: Ready");
  SPI.begin();
}

void serialEvent() {

  while (Serial.available()) {
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
  // need to convert 8-bit integers into 12 bit integers.
  R = atoi(iR)*16;
  G = atoi(iG)*16;
  B = atoi(iB)*16;


  // here we send the command to illuminate the led strips, using values 0-8,
  // where 0 is all on or 1-8 is the unique id of each.
  if ((id) > 0) {
    go_led(id, R, G, B);
  } else {
    for (int i = 1; i < n_bulbs + 1; i++) {
      go_led(id, R, G, B);
    }
  }

  delay(5);
}

void go_led(int i, uint16_t r, uint16_t g, uint16_t b) {

  // first work out pwm channel is r, (g an b channels are +1 and +2)
  int r_chan = (i - 1) * 4;
  int g_chan = r_chan + 1;
  int b_chan = r_chan + 2;

  // showtime!
  pwm.setPWM(r_chan, 4095 - r, r);
  pwm.setPWM(g_chan, 4095 - g, g);
  pwm.setPWM(b_chan, 4095 - b, b);

}

void loop() {
}



