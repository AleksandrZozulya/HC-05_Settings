#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial bt(2, 3); // RX, TX

String inputName = "";
bool nameSent = false;

void chooseBtName(); // Вызывать функцию в loop
void changeBtName(); // Вызывать функцию в setup

void setup()
{
  bt.begin(9600);       // Скорость для AT-команд (обычно 9600)
  Serial.begin(115200); // Для отладки

  delay(1000);
}

void loop()
{
}

void chooseBtName()
{
  if (Serial.available())
  {
    char c = Serial.read();
    if (c == '\n' || c == '\r')
    {
      if (inputName.length() > 0 && !nameSent)
      {
        String command = "AT+NAME=" + inputName;
        bt.println(command);

        Serial.print("Отправлена команда: ");
        Serial.println(command);
        nameSent = true; // Больше не отправлять повторно
      }
    }
    else
    {
      inputName += c;
    }
  }

  // Ответ от bt-модуля
  if (bt.available())
  {
    char c = bt.read();
    Serial.print(c);
  }
}
void changeBtName()
{
  Serial.println("Sending rename command...");

  // Переименовать модуль на "My_BT_Device"
  bt.println("AT+NAME=My_BT_Device");

  delay(1000); // Ждем ответ

  // Показать ответ от модуля
  while (bt.available())
  {
    char c = bt.read();
    Serial.print(c);
  }

  Serial.println("\nRename command sent.");
}
