/*
Stolen from the "mqtt_esp8266" example from PubSubClient library,
so probably some vestigial stuff like publishing on "outTopic".
Lots of room for improvement, esp power usage!
For each song receiver module the appropriate song must be
hardcoded in char song AND client name changed on line 153.
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
const char* ssid = "Xperia_XZ1";
const char* password = "nono31120";
const char* mqtt_server = "192.168.43.245";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int message_count=0;
int jeu_initialise = 0;


void setup() {
  pinMode(BUILTIN_LED, OUTPUT);// Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

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
  /*for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }*/
  Serial.println();
  message_count++;
  //Initialize a game
  if ((char)payload[0]=='I' && jeu_initialise == 0)
  {
     //INSERT GAME CODE
     Serial.println("Initialisation d'une partie");
     jeu_initialise = 1;
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("LiFi")) ///////////////THIS MUST BE A UNIQUE NAME FOR EACH ESP8266
    {  
      Serial.println("connected");
      client.subscribe("Initialisation");
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
}
