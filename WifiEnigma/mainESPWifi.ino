#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>  // This library is already built in to the Arduino IDE
#include <LiquidCrystal_I2C.h> //This library you can add via Include Library > Manage Library > 

int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

int scanButton = 12; //D6 (gpio12)
int naviButton = 14; //D5 (gpio14)

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
int wifiUnhackingSolved = 0;
int battleIASolved = 0;
int domoticSolved =0;
char song = '2';
int i=0;
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


//Variables for the whole game functionning
char* face_id = "1-WiFi";
int jeu_initialise = 1; //A MODIFIER EN '0' APRES LES TESTS
bool attached_to_base = false;
bool enigma_solved = false;


void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); 

  //Initialiaze the secretKey and the encrypted message
  secretKey = random_string(4);
  encryptedPassword = random_string(4);

  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 

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

String calculateXOR(String encryptedPassword, String secretKey) 
{

  String xorResult = "";
  for(int i =0; i < encryptedPassword.length();i++)
  {  
    char curCharPassword;
    curCharPassword = encryptedPassword.charAt(i);
    switch (curCharPassword) 
    {
      case '0':
         encryptedPasswordArray[i*4] = '0'; encryptedPasswordArray[i*4+1] = '0'; encryptedPasswordArray[i*4+2] = '0'; encryptedPasswordArray[i*4+3] = '0';
         break;
      case '1':
         encryptedPasswordArray[i*4] = '0'; encryptedPasswordArray[i*4+1] = '0'; encryptedPasswordArray[i*4+2] = '0'; encryptedPasswordArray[i*4+3] = '1';
         break;
      case '2':
         encryptedPasswordArray[i*4] = '0'; encryptedPasswordArray[i*4+1] = '0'; encryptedPasswordArray[i*4+2] = '1'; encryptedPasswordArray[i*4+3] = '0';
         break;
      case '3':
         encryptedPasswordArray[i*4] = '0'; encryptedPasswordArray[i*4+1] = '0'; encryptedPasswordArray[i*4+2] = '1'; encryptedPasswordArray[i*4+3] = '1';
         break;
      case '4':
         encryptedPasswordArray[i*4] = '0'; encryptedPasswordArray[i*4+1] = '1'; encryptedPasswordArray[i*4+2] = '0'; encryptedPasswordArray[i*4+3] = '0';
         break;
      case '5':
         encryptedPasswordArray[i*4] = '0'; encryptedPasswordArray[i*4+1] = '1'; encryptedPasswordArray[i*4+2] = '0'; encryptedPasswordArray[i*4+3] = '1';
         break;
      case '6':
         encryptedPasswordArray[i*4] = '0'; encryptedPasswordArray[i*4+1] = '1'; encryptedPasswordArray[i*4+2] = '1'; encryptedPasswordArray[i*4+3] = '0';
         break;
      case '7':
         encryptedPasswordArray[i*4] = '0'; encryptedPasswordArray[i*4+1] = '1'; encryptedPasswordArray[i*4+2] = '1'; encryptedPasswordArray[i*4+3] = '1';
         break;
      case '8':
         encryptedPasswordArray[i*4] = '1'; encryptedPasswordArray[i*4+1] = '0'; encryptedPasswordArray[i*4+2] = '0'; encryptedPasswordArray[i*4+3] = '0';
         break;
      case '9':
         encryptedPasswordArray[i*4] = '1'; encryptedPasswordArray[i*4+1] = '0'; encryptedPasswordArray[i*4+2] = '0'; encryptedPasswordArray[i*4+3] = '1';
         break;
      default:
         encryptedPasswordArray[i*4] = '0'; encryptedPasswordArray[i*4+1] = '0'; encryptedPasswordArray[i*4+2] = '0'; encryptedPasswordArray[i*4+3] = '0';
         break;
    }
    
  }
  
  for(int i =0; i < secretKey.length();i++)
  {  
    char curCharKey;
    curCharKey = secretKey.charAt(i);
    switch (curCharKey) 
    {
      case '0':
         secretKeyArray[i*4] = '0'; secretKeyArray[i*4+1] = '0'; secretKeyArray[i*4+2] = '0'; secretKeyArray[i*4+3] = '0';
         break;
      case '1':
         secretKeyArray[i*4] = '0'; secretKeyArray[i*4+1] = '0'; secretKeyArray[i*4+2] = '0'; secretKeyArray[i*4+3] = '1';
         break;
      case '2':
         secretKeyArray[i*4] = '0'; secretKeyArray[i*4+1] = '0'; secretKeyArray[i*4+2] = '1'; secretKeyArray[i*4+3] = '0';
         break;
      case '3':
         secretKeyArray[i*4] = '0'; secretKeyArray[i*4+1] = '0'; secretKeyArray[i*4+2] = '1'; secretKeyArray[i*4+3] = '1';
         break;
      case '4':
         secretKeyArray[i*4] = '0'; secretKeyArray[i*4+1] = '1'; secretKeyArray[i*4+2] = '0'; secretKeyArray[i*4+3] = '0';
         break;
      case '5':
         secretKeyArray[i*4] = '0'; secretKeyArray[i*4+1] = '1'; secretKeyArray[i*4+2] = '0'; secretKeyArray[i*4+3] = '1';
         break;
      case '6':
         secretKeyArray[i*4] = '0'; secretKeyArray[i*4+1] = '1'; secretKeyArray[i*4+2] = '1'; secretKeyArray[i*4+3] = '0';
         break;
      case '7':
         secretKeyArray[i*4] = '0'; secretKeyArray[i*4+1] = '1'; secretKeyArray[i*4+2] = '1'; secretKeyArray[i*4+3] = '1';
         break;
      case '8':
         secretKeyArray[i*4] = '1'; secretKeyArray[i*4+1] = '0'; secretKeyArray[i*4+2] = '0'; secretKeyArray[i*4+3] = '0';
         break;
      case '9':
         secretKeyArray[i*4] = '1'; secretKeyArray[i*4+1] = '0'; secretKeyArray[i*4+2] = '0'; secretKeyArray[i*4+3] = '1';
         break;
      default:
         secretKeyArray[i*4] = '0'; secretKeyArray[i*4+1] = '0'; secretKeyArray[i*4+2] = '0'; secretKeyArray[i*4+3] = '0';
         break;
    }
    
  }

  Serial.println("Début tableau");
  for(int i =0;  i < encryptedPassword.length()*4; i++) {Serial.print(encryptedPasswordArray[i]);}

  Serial.println("Fin tableau");
  for(int i =0;  i < secretKey.length()*4; i++)
  {
    if(secretKeyArray[i] == '0')
    {
      if(encryptedPasswordArray[i] == '0') {xorResult += "0";}

      else {xorResult += "1";}
    }
    else
    {
      if(encryptedPasswordArray[i] == '0') {xorResult += "1";}

      else {xorResult += "0";}
    }
  }
  return xorResult;

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


void game()
{
  Serial.println("Game has started");
  
  ////////////////////////////////////
  //PLACER ICI LE CODE DU JEU
  ////////////////////////////////////
  
  //Lorsque tout est résolu mettre la valeur enigma_solved à true (ligne suivante)
  //enigma_solved = true ;


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
  }

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println();
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
         //gestion du jeu
         if(strcmp(topic,"game/start")==0 )
         {
           game();
           //? envoyer ack ?
         }

         else if (strcmp(topic,"game/reset")==0)
         {
           reset();
           //? envoyer ack ?
         }
         
      }

    
    }
    else 
    {
      Serial.println("Publish connection/state failed");
    }

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
  if(jeu_initialise == 1)
  {
      //If the wifi Unhacking enigma isn't solved
      if(wifiUnhackingSolved == 0)
      {
        //If the player press the SCAN WIFI BUTTON   
        buttonScanState=digitalRead(scanButton);
        if(buttonScanState == 1)
        {
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
                  Serial.println(WiFi.SSID(i));
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
                    Serial.println(WiFi.SSID(i-1));
                  }                 
                }
              }
              //Just to print the new lis of networks
              Serial.println("Nouvelle liste");
              for(int i=0;i < n+1; i++)
              {
                Serial.println(networks[i]);
              }
           }
    
        }
     
        else
        {
            buttonNaviState = digitalRead(naviButton);
            if( buttonNaviState == 1)
            {
               if(millis() >= time_now + period)
               {
                  time_now += period;
                  client.publish("WifiEnigma", "CallNavi");
                  Serial.println("Call Navi");
               }
            }

        }
      
      Serial.print("encryptedPassword : ");
      Serial.println(encryptedPassword);
      Serial.print("secretKey : ");
      Serial.println(secretKey);
      String xorResult = calculateXOR(encryptedPassword, secretKey);
      Serial.println("Le resultat du XOR est : ");
      Serial.println(xorResult);
      Serial.print(xorResult.length());
            
      }

    
    
        //INSERT NUMERIC PAD CODE
      }
      
      //If the battle versus IA enigma isn't solved
      if(battleIASolved == 0)
      {
        //If the user asked to replay Navi's message
    
        //INSERT CODE TO DISPLAY QUESTIONS ON LCD SCREEN 
        //lcd.clear(); 
        //lcd.setCursor(0,0); // positionne le curseur à la colonne 1 et à la ligne 2 
        //lcd.print("A REMPLACER  : AFFICHAGE DES QUESTIONS");*/
        
      }
      
      //If the domotic enigma is solved
      if(domoticSolved == 1)
      {
         //End of enigma
         client.publish("WifiEnigma", "END OF ENIGMA");
      }

      lcd.setCursor(0, 0);
      // print message
      lcd.print("Hello, World!");
      delay(1000);
      // clears the display to print new message
      lcd.clear();
      // set cursor to first column, second row
      lcd.setCursor(0,1);
      lcd.print("Hello, World!");
      delay(1000);
      lcd.clear(); 
  }
