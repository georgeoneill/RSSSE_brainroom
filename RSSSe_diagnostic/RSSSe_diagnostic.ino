
const int color_length = 3;

char iR[color_length + 1];
char iG[color_length + 1];
char iB[color_length + 1];
int id = 0;
uint8_t R = 0;
uint8_t G = 0;
uint8_t B = 0;

void setup() {

  //serial init
  Serial.begin(9600);
  Serial.setTimeout(5);
  Serial.println("RSSSE Diagnostic: Ready");
//  SPI.begin();

  // put your setup code here, to run once:
  analogWrite(9,0); // 9 = red
    analogWrite(10,0); // 10 = blue
  analogWrite(11,0); // 11 = green

}

void serialEvent(){
  while (Serial.available()) {
//    byte size = Serial.readBytes(iI, id_length);
//    iI[size] = 0;
    byte size = Serial.readBytes(iR, color_length);
    iR[size] = 0;
    size = Serial.readBytes(iG, color_length);
    iG[size] = 0;
    size = Serial.readBytes(iB, color_length);
    iB[size] = 0;
  }

  // need to convert 8-bit integers into 12 bit integers.
  R = atoi(iR);
  G = atoi(iG);
  B = atoi(iB);
  
  Serial.print(R);
  Serial.print('\n');
  Serial.print(G);
   Serial.print('\n');
  Serial.print(B);
   Serial.print('\n');

   
   analogWrite(9,R); // 9 = red
    analogWrite(10,G); // 10 = blue
  analogWrite(11,B); // 11 = green

  delay(5);
}

void loop() {
//   put your main code here, to run repeatedly:
//  for(int ii = 1; ii < 256; ii++){
//    analogWrite(9,ii);
//     analogWrite(10,ii);
//      analogWrite(11,ii);
//    delay(20);
//  }
}
