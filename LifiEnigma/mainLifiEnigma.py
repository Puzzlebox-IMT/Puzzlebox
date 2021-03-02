import time
import paho.mqtt.client as mqtt
import sys

#If you must add proagrams in other repertories, add the path of the repertory which contains the programm with the command below
#sys.path.append('path')

#Import the functions of this program
#from program import *

#Flag that determine if you solve the enigma
lifiEnigmaSolved = False

HOST="localhost"
PORT=1883

def on_connect(client, userdata, flags, rc):

    print("Connected to {0} with result code {1}".format(HOST, rc))

def on_message(client, userdata, msg):

    currentPayload = msg.payload
    currentPayload = currentPayload.decode("utf-8")  #Convert the current payload from bytes to string
    currentTopic = msg.topic
    if(currentTopic == "LifiEnigma"):

       payloadsWifiEnigma.append(currentPayload) #Insert the current payload on a list

    else:

       print("Unknown topic")

    #print("Message received on topic {0}: {1}".format(msg.topic, msg.payload))



#Insert the code of your enigma here. You can use functions if you want
def lifiEnigmaRun():

    client = mqtt.Client() 
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(HOST,PORT,300)
    client.subscribe("WifiEnigma")

    client.loop_start()

    try:

        #Avoid an overheat of the processor
        while(lifiEnigmaSolved != True):

            #Insert the code of your Enigma here
            time.sleep(0.5)
            print("LifiEnigma")

    except KeyboardInterrupt:

        client.loop_stop()
        pass



#Main for your tests
if(__name__ == '__main__'):

   lifiEnigmaRun()
