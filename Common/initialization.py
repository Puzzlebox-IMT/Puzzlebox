import paho.mqtt.client as mqtt

def initializeGame():

    entree="blocked"
    #Configuration du RPI en tant que client
    client = mqtt.Client()

    #Connexion au broker MQTT
    client.connect("localhost",1883,300)

    while (entree != ''):

          print("Bienvenue dans le merveilleux univers de Puzzlebox")
          entree = input("Pour démarrer une partie appuyez sur ENTREE au clavier ou pressez le bouton central de la Puzzlebox\n")

    #Payload dédiée à l'initialisation
    client.publish("Initialisation", "I")

if(__name__ == '__main__'):

    initializeGame()
