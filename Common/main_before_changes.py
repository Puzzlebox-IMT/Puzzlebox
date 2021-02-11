import paho.mqtt.client as mqtt
import sys
import time


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

payloadsWifiEnigma = [""] #Initialize a list to collect the payloads from the WifiEnigma topic 
payloadsLifi = [""] #Initialize a list to collect the payloads from the LiFi topic

#Flags which indicates if the enigmas are solved
wifiUnhackingSolved = False
battleAISolved = False
domoticSolved = False

def on_connect(client, userdata, flags, rc): 

    print("Connected to {0} with result code {1}".format(HOST, rc)) 


def on_message(client, userdata, msg): 

    currentPayload = msg.payload
    currentPayload = currentPayload.decode("utf-8")  #Convert the current payload from bytes to string
    currentTopic = msg.topic
    if(currentTopic == "WifiEnigma"):

       payloadsWifiEnigma.append(currentPayload) #Insert the current payload on a list

    elif(currentTopic == "LiFi"):

       payloadsLifi.append(currentPayload)
    else:

       print("Unknown topic")

    print("Message received on topic {0}: {1}".format(msg.topic, msg.payload))


client = mqtt.Client() 
client.on_connect = on_connect
client.on_message = on_message

client.connect(HOST,PORT,300)
client.subscribe("WifiEnigma")

client.loop_start()

try:
  while True:

      time.sleep(1)
      if(wifiUnhackingSolved == False):

        print(payloadsWifiEnigma)
        print(payloadsWifiEnigma[-1])
        if(payloadsWifiEnigma[-1] == "CallNavi"):

           print("Caca")

      elif(battleAISolved == False):

           print("Pipi") 


except KeyboardInterrupt:

     client.loop_stop()
     pass


