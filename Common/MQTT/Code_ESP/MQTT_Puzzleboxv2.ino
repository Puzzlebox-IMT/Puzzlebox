
#include <WiFi.h> //ou #include <ESP8266WiFi.h> si ESP8266
#include <PubSubClient.h>

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

//Variables jeu
char* face_id = "1-WiFi";
bool attached_to_base = false;
bool enigma_solved = false;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println();
  //Gestion des messages MQTT
  //si le raspberry souhaite savoir si la face est connecté sur la base
  if (strcmp(topic,"connection/ask_state")==0){
   
    String payload = "{\"face_id\":";
    payload += face_id;
    payload += ",\"state\":";
    payload += attached_to_base;
    payload += "}";

    
    if (client.publish("connection/state", (char*) payload.c_str())) {
      Serial.println("Publish connection/state ok");
      Serial.println("");
    }
    else {
      Serial.println("Publish connection/state failed");
    }

    if(attached_to_base == true){
      client.subscribe("game/#");
      //rajouter la souscription aux topics propres au jeu
    }
  }

  //gestion du jeu
  if (strcmp(topic,"game/start")==0 ){
    game();
    //? envoyer ack ?
  }

  if (strcmp(topic,"game/reset")==0){
  reset();
  //? envoyer ack ?
  }

  //TOPICS PROPRES AU JEU
  //A Rajouter


}

void game(){
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

  //check état interrupteur TODO
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
  }
}
