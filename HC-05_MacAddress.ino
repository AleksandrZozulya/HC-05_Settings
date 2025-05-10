#include <SoftwareSerial.h>

#define arduino_rx = 2;
#define arduino_tx = 3;

SoftwareSerial mySerial(arduino_rx, arduino_tx);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.print("Connect...");

  while (!mySerial.available()) {
    Serial.print(".");
    mySerial.println("AT");
    delay(500);  
  }

  Serial.println();
  Serial.println("<<< Start! >>>");
}

void loop() {
  
  if (mySerial.available()) {
    char c = mySerial.read();
    Serial.print(c);
  }
  if (Serial.available()) {
    char c = Serial.read();
    mySerial.write(c);
  }
}
