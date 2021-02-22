import multiprocessing as mp
import time
import paho.mqtt.client as mqtt
import sys
from initialization import *

sys.path.append('../WifiEnigma')
sys.path.append('../LifiEnigma')

sys.path.append('../WifiEnigma/WifiUnhacking')
sys.path.append('../WifiEnigma/ZeldaAutomation')
sys.path.append('../WifiEnigma/BattleAI')

#Import Enigma's main
from mainWifiEnigma import *
from mainLifiEnigma import *

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
    if(currentTopic == "main"):

       payloadsWifiEnigma.append(currentPayload) #Insert the current payload on a list

    else:

       print("Unknown topic")

    #print("Message received on topic {0}: {1}".format(msg.topic, msg.payload))

if(__name__ == '__main__'):

    #Waiting for the player launching the game
    initializeGame()

    client = mqtt.Client() 
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(HOST,PORT,300)
    client.subscribe("WifiEnigma")

    client.loop_start()
    ctx = mp.get_context('spawn')

    try:

        #Execute wifiUnhackingEnigma
        wifiProcess = ctx.Process(target=wifiEnigmaRun)
        lifiProcess = ctx.Process(target=lifiEnigmaRun)

        wifiProcess.start()
        lifiProcess.start()

        print("Jeu en cours")
        wifiProcess.join()
        lifiProcess.join()

    except KeyboardInterrupt:

        client.loop_stop()
        pass


