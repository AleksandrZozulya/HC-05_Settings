#include <Arduino.h>
#include <SoftwareSerial.h>

//SoftwareSerial Serial3(2, 3); // RX (to HC-05 TX), TX (to HC-05 RX)

String inputName = "";
bool nameSent = false;

void chooseSerial3Name(); // Call this in loop()
void changeSerial3Name(); // Call this in setup() if needed

void setup()
{
  Serial3.begin(9600);       // Baud rate for AT commands (usually 9600)
  Serial.begin(115200); // For serial monitor communication

  delay(1000);

  // Uncomment the line below to send a fixed name automatically at startup:
   changeSerial3Name();
}

void loop()
{
  //chooseSerial3Name();
}

void chooseSerial3Name()
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
        Serial3.println(command);

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

  // Read response from the Serial3 module
  if (Serial3.available())
  {
    char c = Serial3.read();
    Serial.print(c);
  }
}

void changeSerial3Name()
{
  Serial.println("Sending rename command...");

  // Rename the module to "My_Serial3_Device"
  Serial3.println("AT+NAME=L-0659");

  delay(1000); // Wait for a response

  // Print response from the Serial3 module
  while (Serial3.available())
  {
    char c = Serial3.read();
    Serial.print(c);
  }

  Serial.println("\nRename command sent.");
}
