#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3); // RX, TX

void setup() {
  bluetooth.begin(9600);      // Скорость для AT-команд (обычно 9600)
  Serial.begin(115200);       // Для отладки

  delay(1000); // Небольшая задержка перед началом

  Serial.println("Sending rename command...");

  // Переименовать модуль на "My_BT_Device"
  bluetooth.println("AT+NAME=My_BT_Device");

  delay(1000); // Ждем ответ

  // Показать ответ от модуля
  while (bluetooth.available()) {
    char c = bluetooth.read();
    Serial.print(c);
  }

  Serial.println("\nRename command sent.");
}

void loop() {
  // Ничего не делаем
}
