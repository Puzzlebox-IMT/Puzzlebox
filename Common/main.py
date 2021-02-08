import paho.mqtt.client as mqtt
import sys

sys.path.append('../WifiEnigma/WifiUnhacking')
sys.path.append('../WifiEnigma/ZeldaAutomation')
sys.path.append('../WifiEnigma/BattleAI')

#IMPORTS OF THE WIFI UNHACKING ENIGMA
import wifi_Puzzlebox
import wifiUnhackingSolved

#IMPORTS OF THE WIFI DOMOTIC ENIGMA
import zelda_home_public
import domoticEnigmaSolved

HOST="localhost"
PORT=1883


def on_connect(client, userdata, flags, rc): 

    print("Connected to {0} with result code {1}".format(HOST, rc)) 


def on_message(client, userdata, msg): 

    print("Message received on topic {0}: {1}".format(msg.topic, msg.payload))


client = mqtt.Client() 
#client.on_connect = on_connect
client.on_message = on_message

client.connect(HOST,PORT,300)
client.subscribe("WifiEnigma")
client.loop_forever()

