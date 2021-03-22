#imports librairies
import time
import paho.mqtt.client as mqtt
import sys
import RPi.GPIO as GPIO
from threading import Thread

sys.path.append('BattleAI')
sys.path.append('ZeldaAutomation')



#IMPORTS OF THE WIFI BATTLE AI
#from question import *


#IMPORTS OF THE WIFI DOMOTIC ENIGMA
from zelda_home_public import *


#MQTT SETTINGS
HOST="localhost"
PORT=1883

#Flags which indicates if the enigmas are solved
wifiUnhackingSolved = False
battleAISolved = False
domoticSolved = False

wifiEnigmaSolved = False
game_started = False


def on_connect(client, userdata, flags, rc): 
    print("Connected to {0} with result code {1}".format(HOST, rc)) 


def on_message(client, userdata, msg): 

    currentPayload = msg.payload
    currentPayload = currentPayload.decode("utf-8") 
    currentTopic = msg.topic
    if(currentTopic == "connection/state"):
       print(currentPayload)
       sleep(2)
       client.publish('game/start',"1")
    elif(currentTopic == "topic2"):
        print('topic')
    else:  
       print("Unknown topic")
    print("Message received on topic {0}: {1}".format(msg.topic, msg.payload))




def on_publish(client,userdata,result):             #create function for callback
    print("data published \n")
    pass


def button_callback(channel):
    #Début du jeu
    Thread(target = game_start).start()

        
    
def game_start():
    client.publish('connection/ask_state',"1")
    sleep(1)
    
client = mqtt.Client() 
client.on_connect = on_connect
client.on_message = on_message
client.onpublish = on_publish


def main():
 


    client.connect(HOST,PORT,300)
    client.subscribe("connection/#")
    client.subscribe("game/#")
    client.subscribe("WifiEnigma/#")
 
    client.loop_start()

    try:
        GPIO.setwarnings(False) # Ignore warning for now
        GPIO.setmode(GPIO.BOARD) # Use physical pin numbering
        GPIO.setup(10, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)

        GPIO.add_event_detect(10,GPIO.RISING,bouncetime=500,callback=button_callback)
        
        
        
        #While the WifiEnigma is not solved
#         while (wifiEnigmaSolved != True):
# 
#            while (wifiUnhackingSolved != True):

#    
#               client.publish("connection/ask_state","1")
#               time.sleep(0.5) 

    except KeyboardInterrupt:
        client.loop_stop()
        pass


if(__name__ == '__main__'):
    main()
