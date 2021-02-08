import paho.mqtt.client as mqtt


#Configuration du RPI en tant que client
client = mqtt.Client()

#Connexion au broker MQTT
client.connect("localhost",1883,300)

#Payload dédiée à l'initialisation
client.publish("WifiEnigma", "3")
