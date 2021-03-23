
//Define the variable that contains the led 
#define ledPin 4 
int state = 0; 
void setup() { 
  //Setting the pin mode and initial LOW  
  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, LOW); 
  Serial.begin(9600); // Default communication rate 
} 
void loop() { 
  // Checks if the data is coming from the serial port 
  if(Serial.available() > 0){  
    state = Serial.read(); // Read the data from the serial port 
 } 
 //Deciding functions for LED on and off  
 if (state == '0') { 
  digitalWrite(ledPin, LOW); // Turn LED OFF 
  // Send back, to the phone, the String "LED: ON" 
  Serial.println("LED: OFF");  
  state = 0; 
 } 
 else if (state == '1') { 
  digitalWrite(ledPin, HIGH); 
  Serial.println("LED: ON");; 
  state = 0; 
 } else if (state == '2') { 
  code(); //Start Morse Code
  Serial.println("LED: CODE MORSE");; 
  state = 0; 
 }  
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
void dot () {digitalWrite(ledPin,HIGH); delay (300); digitalWrite(ledPin,LOW); delay (300);}//the dot this code make the led on for 300 than off for 300
void dash () {digitalWrite(ledPin,HIGH); delay (900); digitalWrite(ledPin,LOW); delay (300);}//the dash this code make the led on for 900 than off for 300
void shortspace () {delay(600);}//space between letters
