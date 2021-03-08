import time
import paho.mqtt.client as mqtt
import sys
import os

sys.path.append('WifiUnhacking')
sys.path.append('ZeldaAutomation')
sys.path.append('BattleAI')

#IMPORTS OF THE WIFI UNHACKING ENIGMA
from wifi_Puzzlebox import *
#from wifiUnhackingSolved import *

#IMPORTS OF THE WIFI BATTLE AI
from zelda_home_public import *
from voice import *


#IMPORTS OF THE WIFI DOMOTIC ENIGMA
import zelda_home_public
import domoticEnigmaSolved

payloadsWifiEnigma = ["vide"]

HOST="localhost"
PORT=1883

#Flags which indicates if the enigmas are solved
wifiUnhackingSolved = False
battleAISolved = False
domoticSolved = False
wifiEnigmaSolved = False

def on_connect(client, userdata, flags, rc): 

    print("Connected to {0} with result code {1}".format(HOST, rc)) 


def on_message(client, userdata, msg): 

    currentPayload = msg.payload
    currentPayload = currentPayload.decode("utf-8")  #Convert the current payload from bytes to string
    currentTopic = msg.topic
    if(currentTopic == "WifiEnigma"):

       payloadsWifiEnigma.append(currentPayload) #Insert the current payload on a list

    else:

       print("Unknown topic")

    #print("Message received on topic {0}: {1}".format(msg.topic, msg.payload))


def storytelling():

    message = "Link! Ganon prend possession de moi, je commence à perdre connaissance. "
    message += "J'ai analysé le programme malveillant de Ganon et j'ai pu voir qu'il utilise une simple fonction XOR entre la clé de chiffrement et le mot de passe chiffré."
    message += "J'ai eu le temps de remplacer le mot de passe chiffré par le nom de ton réseau Wi-Fi corrompu et d'imprimer une feuille contenant le mot de passe chiffré et les opérations que tu devras réaliser. Lorsque tu auras terminé, insère le mot de passe sur le digicode."
    message += "Link! Sauve moi mon ami, l'avenir de la maison dépend de toi!"
    os.system('pico2wave -l  fr-FR -w voice.wav "' + message + '" && aplay voice.wav')
    time.sleep(1)
    os.system('sudo rm -rf voice.wav')


def wifiEnigmaRun():

    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(HOST,PORT,300)
    client.subscribe("WifiEnigma")

    client.loop_start()

    try:

        storytelling()
        #While the WifiEnigma is not solved
        while (wifiEnigmaSolved != True):

           while (wifiUnhackingSolved != True):

              if(payloadsWifiEnigma[-1] == "CallNavi"):

                  #storytelling()
                  time.sleep(0.5)
                  print("WifiEnigma")


           while (battleAISolved != True):

              if(payloadsWifiEnigma[-1] == "CallNavi"):

                 print("Wifi")


    except KeyboardInterrupt:

        client.loop_stop()
        pass


if(__name__ == '__main__'):

    wifiEnigmaRun()
