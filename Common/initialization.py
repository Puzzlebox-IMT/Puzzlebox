import paho.mqtt.client as mqtt

entree=""
#Configuration du RPI en tant que client
client = mqtt.Client()

#Connexion au broker MQTT
client.connect("localhost",1883,300)

while (entree != "Q"):

  entree = input("Demarrer une partie en appuyant sur Q \n")


#Payload dédiée à l'initialisation
client.publish("Initialisation", "I")

"""while (entree != "A"):

  entree = input("Resoudre enigme Unhacking en appuyant sur A \n")

while (entree != "B"):

  entree = input("Resoudre enigme BATTLE AI en appuyant sur B \n")

"""
