#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define LEDpin1 4 //1re LED branchée à GPIO4
#define LEDpin2 5 //2me à GPIO 5

char instruction; //message reçu par bluetooth;
int etatLED1 = 0, etatLED2 = 0;
bool isEnigmaSolved = false;
bool isCodeSolved = false;
char enigma[] = "Quelle est la couleur du cheval blanc d'Henri IV ?";

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  pinMode(LEDpin1, OUTPUT);
  pinMode(LEDpin2, OUTPUT);
  Serial.println("The device started, now you can pair it with bluetooth!");
  
}

void loop() {
  char message;

  if (SerialBT.available()) {
    message = SerialBT.read(); // lecture du message reçu
    Serial.write(message);
  }
  
  if (!isEnigmaSolved) {
    SerialBT.println(enigma);

    if (message != instruction) {
      instruction = message;
    }

    if (instruction == 'b') {
      isEnigmaSolved = true;
    }
    
  } else {
    //enigma is solved, display morse code
    if (!isCodeSolved) {
      SerialBT.println("Trouvez le bon code.");
      code();
      SerialBT.println("Tu as 10 secondes pour rentrer le code");
      delay(10000);

      if (message != instruction) {
      instruction = message;
      }

      if (instruction == 'i') {
        digitalWrite(LEDpin1, HIGH);
        isCodeSolved = true;
      } else {
        SerialBT.println("Essaye encore");
      }
      
    } else {
      SerialBT.println("Bravo! Vous avez vaincu Ultron");
    }
  }
  
  /*if (Serial.available()) {
    SerialBT.write(Serial.read());
  }*/
  if (SerialBT.available()) {
    message = SerialBT.read(); // lecture du message reçu
    Serial.write(message);
  }
    delay(2000);
}

void code() {
    lI();
    lE();
    lE();
    lE();
    space();
    n8();
    n0();
    n2();
    dot();
    n1();
    n5();
    }

void lA () {dot();dash();shortspace();}//letter A in morse code!
void lB () {dash();dot();dot();dot();shortspace();}//same for B
void lC () {dash();dot();dash();dot();shortspace();}
void lD () {dash();dot();dot();shortspace();}
void lE () {dot();shortspace();}
void lF () {dot();dot();dash();dot();shortspace();}
void lG () {dash();dash();dot();shortspace();}
void lH () {dot();dot();dot();dot();shortspace();}
void lI () {dot();dot();shortspace();}
void lJ () {dot();dash();dash();dash();shortspace();}
void lK () {dash();dot();dash();shortspace();}
void lL () {dot();dash();dot();dot();shortspace();}
void lM () {dash();dash();shortspace();}
void lN () {dash();dot();shortspace();}
void lO () {dash();dash();dash();shortspace();}
void lP () {dot();dash();dash();dot();shortspace();}
void lQ () {dash();dash();dot();dash();shortspace();}
void lR () {dot();dash();dot();shortspace();}
void lS () {dot();dot();dot();shortspace();}
void lT () {dash();shortspace();}
void lU () {dot();dot();dash();shortspace();}
void lV () {dot();dot();dot();dash();shortspace();}
void lW () {dot();dash();dash();shortspace();}
void lX () {dash();dot();dot();dash();shortspace();}
void lY () {dash();dot();dash();dash();shortspace();}
void lZ () {dash();dash();dot();dot();shortspace();}
void n1 () {dot();dash();dash();dash();dash();shortspace();}//number 1 in morse code
void n2 () {dot();dot();dash();dash();dash();shortspace();}
void n3 () {dot();dot();dot();dash();dash();shortspace();}
void n4 () {dot();dot();dot();dot();dash();shortspace();}
void n5 () {dot();dot();dot();dot();dot();shortspace();}
void n6 () {dash();dot();dot();dot();dot();shortspace();}
void n7 () {dash();dash();dot();dot();dot();shortspace();}
void n8 () {dash();dash();dash();dot();dot();shortspace();}
void n9 () {dash();dash();dash();dash();dot();shortspace();}
void n0 () {dash();dash();dash();dash();dash();shortspace();}
void space () {delay (1200);}//space between words
void dot () {digitalWrite(LEDpin1,HIGH); delay (300); digitalWrite(LEDpin1,LOW); delay (300);}//the dot this code make the led on for 300 than off for 300
void dash () {digitalWrite(LEDpin1,HIGH); delay (900); digitalWrite(LEDpin1,LOW); delay (300);}//the dash this code make the led on for 900 than off for 300
void shortspace () {delay(600);}//space between letters
