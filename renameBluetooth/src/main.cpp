#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial bt(2, 3); // RX (to HC-05 TX), TX (to HC-05 RX)

String inputName = "";
bool nameSent = false;

void chooseBtName(); // Call this in loop()
void changeBtName(); // Call this in setup() if needed

void setup()
{
  bt.begin(9600);       // Baud rate for AT commands (usually 9600)
  Serial.begin(115200); // For serial monitor communication

  delay(1000);

  // Uncomment the line below to send a fixed name automatically at startup:
  // changeBtName();
}

void loop()
{
  chooseBtName();
}

void chooseBtName()
{
  // Read input from serial monitor
  if (Serial.available())
  {
    char c = Serial.read();
    if (c == '\n' || c == '\r')
    {
      if (inputName.length() > 0 && !nameSent)
      {
        String command = "AT+NAME=" + inputName;
        bt.println(command);

        Serial.print("Command sent: ");
        Serial.println(command);
        nameSent = true; // Prevent resending
      }
    }
    else
    {
      inputName += c;
    }
  }

  // Read response from the BT module
  if (bt.available())
  {
    char c = bt.read();
    Serial.print(c);
  }
}

void changeBtName()
{
  Serial.println("Sending rename command...");

  // Rename the module to "My_BT_Device"
  bt.println("AT+NAME=My_BT_Device");

  delay(1000); // Wait for a response

  // Print response from the BT module
  while (bt.available())
  {
    char c = bt.read();
    Serial.print(c);
  }

  Serial.println("\nRename command sent.");
}
