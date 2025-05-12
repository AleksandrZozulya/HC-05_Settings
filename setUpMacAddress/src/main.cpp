#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(2, 8); //tx rx

void sendData(const String& data) {
  Bluetooth.println(data);
}

void setUpMacAddress();

void setup() {
  Bluetooth.begin(9600);
  Serial.begin(115200);
  setUpMacAddress();
}

void loop() {
  
}

void setUpMacAddress() {
  // send AT commands 
  sendData("AT+UART=9600,0,0");
  sendData("AT+CMODE=0");
  sendData("AT+BIND=20,4,32569f"); //MAC Address
  sendData("AT+ROLE=1");

  // awaiting BT requst
  while (!Bluetooth.available()) {
    delay(100); 
  }

  Serial.println("DONE");
}
