# -*- coding: utf-8 -*-

import RPI.GPIO as GPIO

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(10, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
while True:
    if(GPIO.input(8)==True):
        print ("Voix 1 sélectionnée")
    elif(GPIO.input(10)==True):
        print ("Voix 2 sélectionné")
    elif(GPIO.input(12)==True):
        print ("Voix 3 sélectionnée")
        
        
