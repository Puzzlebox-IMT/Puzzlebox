//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define LEDpin1 4 //1re LED branchée à GPIO4
#define LEDpin2 5 //2me à GPIO 5

char instruction; //message reçu par bluetooth;
int etatLED1 = 0, etatLED2 = 0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  pinMode(LEDpin1, OUTPUT);
  pinMode(LEDpin2, OUTPUT);
  Serial.println("The device started, now you can pair it with bluetooth!");
  
}

void loop() {
  char message;
  
  /*if (Serial.available()) {
    SerialBT.write(Serial.read());
  }*/
  if (SerialBT.available()) {
    message = SerialBT.read(); // lecture du message reçu
    Serial.write(message);
  }

  if (message != instruction) {
    instruction = message;
  }

  if (instruction == 'a')
    {
      digitalWrite(LEDpin1, HIGH);
      digitalWrite(LEDpin2, LOW);
      etatLED1 = 1;
      etatLED2 = 0;
      SerialBT.println("LED 1 allumee, LED 2 eteinte");
    }
    else if (instruction == 'b')
    {
      digitalWrite(LEDpin1, LOW);
      digitalWrite(LEDpin2, HIGH);
      etatLED1 = 0;
      etatLED2 = 1;
      SerialBT.println("LED 1 eteinte, LED 2 allumee");
    }
    else if (instruction == 'c')
    {
      digitalWrite(LEDpin1, HIGH);
      digitalWrite(LEDpin2, HIGH);
      etatLED1 = 1;
      etatLED2 = 1;
      SerialBT.println("Les 2 LEDs allumees");
    }
    else if (instruction == 'd')
    {
      digitalWrite(LEDpin1, LOW);
      digitalWrite(LEDpin2, LOW);
      etatLED1 = 0;
      etatLED2 = 0;
      SerialBT.println("Les 2 LEDs eteinte");
    }
    delay(200);
}
