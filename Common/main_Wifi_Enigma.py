import paho.mqtt.client as mqtt
import sys
import time
import threading

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

class thread_Wifi_Enigma(threading.Thread):

       def __init__(self,stop_event):


           threading.Thread.__init__(self)
           self.stop_event = stop_event

           #Flags which indicates if the enigmas are solved
           self.wifiUnhackingSolved = False
           self.battleAISolved = False
           self.domoticSolved = False

           self.wifiEnigmaSolved = False
           self.currentAction = ""


       def run(self):


           client = mqtt.Client()
           client.connect(HOST,PORT,300)
           client.subscribe("WifiEnigma")
           client.loop_start()
           while not self.stop_event.wait(1):

                 try:

                     while (not self.wifiEnigmaSolved):

                        time.sleep(1)
                        print("Demmarage du thread")
                        while(self.currentAction != ""):

                           payloadsWifi
                           if(wifiUnhackingSolved == False):

                              print(payloadsWifiEnigma)
                              print(payloadsWifiEnigma[-1])
                              if(payloadsWifiEnigma[-1] == "CallNavi"):

                                 print("Caca")

                           elif(battleAISolved == False):

                              print("Pipi")

                           currentAction = "" 
                           time.sleep(0.050)


                 except KeyboardInterrupt:

                    client.loop_stop()
                    pass

       def action(self, payload):

           self.currentAction = payload
           return self.currentAction

       def result():

           return self.wifiEnigmaSolved
