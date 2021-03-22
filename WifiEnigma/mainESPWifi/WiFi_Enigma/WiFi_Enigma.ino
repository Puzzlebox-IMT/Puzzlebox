#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>  // This library is already built in to the Arduino IDE
#include <LiquidCrystal_I2C.h> //This library you can add via Include Library > Manage Library > 
#include <Stepper.h>
#include "Keypad.h"

//Paramètres Ecran
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

//Paramètres Bouton
int scanButton = 19; //D6 (gpio12)
int naviButton = 14; //D5 (gpio14)

//Paramètres Keypad
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {2,0, 4, 16}; 
byte colPins[COLS] = {17, 5, 18}; 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


//Paramètres StepperMotor
const int stepsPerRevolution = 2048;
Stepper myStepper = Stepper(stepsPerRevolution, 25,26, 27, 14);


//Paramètres Wifi
const char* ssid = "PuzzleBox";
const char* password = "puzzlelpd2021";
const char* mqtt_server = "192.168.4.1";

//Paramètres MQTT
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//Variables for enigma
int buttonScanState = 0;
int buttonNaviState = 0;
long watchdogScanButton = 0;
long watchdogNaviButton = 0;
int period = 2000;
unsigned long time_now = 0;
int randomIndexScanWifi = 0;
String secretKey;
String encryptedPassword;
char encryptedPasswordArray[17];
//encryptedPassword.toCharArray(encryptedPasswordArray, encryptedPassword.length()+1);
char secretKeyArray[17];  
//secretKey.toCharArray(secretKeyArray, secretKey.length()+1);
int passwordSize = 4;


//Variables for the whole game functionning
char* face_id = "1-WiFi";
int jeu_initialise = 1; //A MODIFIER EN '0' APRES LES TESTS
bool attached_to_base = true;
bool enigma_solved = false;
bool wifi_solved = false;


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); 
  

  myStepper.setSpeed(10);
   //Initialiaze the secretKey and the encrypted message,
   //vérifie que l'opération XOR ne retourne pas de résultat contenant A,B,C,D,E,F (impossible de saisir ces caractères sur le pavé numérique)
  do{
    secretKey = random_string(passwordSize);
    encryptedPassword = random_string(passwordSize);
  }while(calculateXOR(secretKey,encryptedPassword)=="error");


  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 

  //LEDS
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);

}


String random_string(int stringLength) 
{
  String randomString = "";
  //Create a random String
  for(int i = 0; i < stringLength; i++)
  {
    randomString += random(10); //Add a random number between 0 and 9 to the randomString
  }
  return randomString;
}


String calculateXOR(String a, String b){
    String res;
    int xorc ;
    for(int i = 0 ; i<passwordSize ; i++){
      xorc = a[i]^b[i];
      //Si une des opérations XOR retourne un résultat supérieur à 9, nous sommes dans le cas A,B,C,D,E,F
      if(xorc > 9){
        res = "error";
        break;
      }
      res = res + xorc;
    }
    return res;
}

void setup_wifi() {
  delay(5);  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void eject(){
  myStepper.step(stepsPerRevolution);  
  myStepper.step(stepsPerRevolution);    
  myStepper.step(stepsPerRevolution); 
  myStepper.step(stepsPerRevolution);  
  myStepper.step(stepsPerRevolution);     
}

void retract(){
  myStepper.step(-stepsPerRevolution);
  myStepper.step(-stepsPerRevolution); 
  myStepper.step(-stepsPerRevolution); 
  myStepper.step(-stepsPerRevolution); 
  myStepper.step(-stepsPerRevolution);
}


void game()
{
  Serial.println("Game has started");

 
      //
      lcd.setCursor(0,0);
      lcd.print("Debut du jeu !");
   ;
       //leds wifi
      digitalWrite(32, HIGH);
      digitalWrite(33, LOW);
 
      //Dérouler notice
      eject();


      
      //If the player press the SCAN WIFI BUTTON  
      bool cond = false;
      do{
      if(wifi_solved == false){
        digitalWrite(32, HIGH);
        digitalWrite(33, LOW);
      }else{
        digitalWrite(32, LOW);
        digitalWrite(33, HIGH);
      }
   
      buttonScanState=digitalRead(scanButton);
      client.loop();
      if(buttonScanState == 1)
      {
         lcd.clear();
         //Avoid to send a bunch of publish while pushing the button
         long now = millis();
         if (now - watchdogScanButton > 2000) 
         {
            watchdogScanButton = now;
            int n = WiFi.scanNetworks(); //Scan the ambiant networks and return the number of scans 
            String networks [n+1]; //Initialize a tab to store the networks
            randomIndexScanWifi = random(n);
            for (int i = 0; i < n+1; i++)
            {
              if(i < randomIndexScanWifi)
              {
                networks[i] = WiFi.SSID(i);
                //Serial.println(WiFi.SSID(i));
              }
              else
              {
                if(i == randomIndexScanWifi) 
                {
                  networks[i] = encryptedPassword;
                }
                else
                {
                  networks[i] = WiFi.SSID(i-1);
                  //Serial.println(WiFi.SSID(i-1));
                }                 
              }
            }
            //Affichage réseaux wifi écran
            for(int i=0;i < n+1; i++)
            {
              //Serial.println(networks[i]);
              
              lcd.setCursor(0,0);
              lcd.print(networks[i]);
              delay(1000);
              lcd.clear(); 
            }
         }

            lcd.setCursor(0,0);
            lcd.print("Cle :");
            lcd.setCursor(0,1);
            lcd.print(secretKey);
            delay(1000);
            lcd.clear();

         String input ;
         String correct = "false";
         do{
          char key = keypad.getKey();
            if(input.length()<4){
              if(key){
                input = input+key;
                 Serial.println(input);
                  lcd.clear();
                  lcd.setCursor(0,0);
                  lcd.print(input);
                 
                }
            }
            else
            {
              if(input == calculateXOR(encryptedPassword, secretKey)){
                correct == "true";
                break;
              }else{
                Serial.println("Mot de passe incorrect");
                lcd.setCursor(0,1);
                lcd.print("MDP incorrect");
                delay(2000);
                input = "";
                lcd.clear();
              }       
            }  
          
          delay(100);
         }while(correct == "false");
          Serial.println("Mot de passe résolu !");
          lcd.setCursor(0,1);
          lcd.print("MDP correct !");
          wifi_solved = true;
          delay(2000);
          lcd.clear();
          delay(1000);
          lcd.clear();
          
          

      }
      delay(100);
      
      //LEDS
      //fin partie 1, activer jauge 1




     //passer au questions (bouton vraiment nécessaire ?)




     //Si question ok déployer trappe ocarina
     //fin partie 2, activer jauge 3

      //mqtt programme reconnaissance etc
      //si ok allumer leds plantes 
      //jouer musique victoire

      //fin partie 3, activer jauge 3
      //enigma_solved = true ;
      //break;
      }while(enigma_solved == false);
  
  //Lorsque tout est résolu mettre la valeur enigma_solved à true (ligne suivante)



  //Ne pas effacer cette partie
  String payload = "{\"face_id\":";
    payload += face_id;
    payload += ",\"game_state\":";
    payload += enigma_solved;
    payload += "}";
  
    if (client.publish("game/state", (char*) payload.c_str())) {
      Serial.println("Publish game/state ok");
    }
    else {
      Serial.println("Publish game/state failed");
    }
}

void reset(){
  client.unsubscribe("game/#");
  enigma_solved = false ;


  //allumer led wifi rouge
  //éteindre led wifi verte

  //jauge 0 

  //éteindre leds questions

  //éteindre leds plante

  //enrouler notice

  //fermer trappe ocarina
  }

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Message MQTT reçu : ");
  Serial.println(topic);
  //Gestion des messages MQTT
  //si le raspberry souhaite savoir si la face est connecté sur la base
  if (strcmp(topic,"connection/ask_state")==0)
  { 
    String payload = "{\"face_id\":";
    payload += face_id;
    payload += ",\"state\":";
    payload += attached_to_base;
    payload += "}";

    
    if (client.publish("connection/state", (char*) payload.c_str())) 
    {
      Serial.println("Publish connection/state ok");
      Serial.println("");
      if(attached_to_base == true)
      {
         client.subscribe("game/#");
         //rajouter la souscription aux topics propres au jeu
         client.subscribe("WifiEnigma/#");
        
         
      }

    }
        
    else 
    {
      Serial.println("Publish connection/state failed");
    }
  }
     //gestion du jeu
    else if(strcmp(topic,"game/start")==0 )
     {
       game();
     }

     

     else if (strcmp(topic,"game/reset")==0)
     {
       reset();
       //? envoyer ack ?
     }

//Topic WifiEnigma
      else if (strcmp(topic,"WifiEnigma/song")==0)
     {
       Serial.write(payload, length);
       //? envoyer ack ?
     }



  

}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(face_id)) ///////////////THIS MUST BE A UNIQUE NAME FOR EACH ESP8266
    {  
      Serial.println("connected");
      //souscription au topic connection
      client.subscribe("connection/#");
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();
  
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
  }
  
//  if(jeu_initialise == 1)
//  {
//    game();
//  }
//     

  


  }
