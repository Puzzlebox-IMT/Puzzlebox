#Tone detection shamelessly stolen from:
#https://benchodroff.com/2017/02/18/using-a-raspberry-pi-with-a-microphone-to-hear-an-audio-alarm-using-fft-in-python/
#!/usr/bin/env python
import pyaudio
from numpy import zeros,linspace,short,fromstring,hstack,transpose,log
from scipy import fft
from time import sleep
from collections import deque
import paho.mqtt.client as mqtt
import requests
import pygame.mixer
from pygame.mixer import Sound
import RPi.GPIO as GPIO

#GPIO stuff
GPIO.setmode(GPIO.BCM)
GPIO.setup(5, GPIO.OUT)#D4 Blue
GPIO.setup(6, GPIO.OUT)#F Down
GPIO.setup(13, GPIO.OUT)#A Right
GPIO.setup(19, GPIO.OUT)#D5 Up
GPIO.setup(26, GPIO.OUT)#B Left

GPIO.output(5, GPIO.LOW)
GPIO.output(6, GPIO.LOW)
GPIO.output(13, GPIO.LOW)
GPIO.output(19, GPIO.LOW)
GPIO.output(26, GPIO.LOW)
#audio stuff maybe
pygame.mixer.init(32000) #turn all of pygame on.
confirm = Sound("OOT_Song_Correct.wav")#change accordingly for your song confirmation sound file name/location
#mqtt stuff
client = mqtt.Client()
client.connect("localhost",1883,300)

#Volume Sensitivity, 0.05: Extremely Sensitive, may give false alarms
#             0.1: Probably Ideal volume
#             1: Poorly sensitive, will only go off for relatively loud
SENSITIVITY= 1.0

#Bandwidth for detection (i.e., detect frequencies within this margin of error of the TONE)
BANDWIDTH = 25

# Alarm frequencies (Hz) to detect (Use audacity to record a wave and then do Analyze->Plot Spectrum)
D4 = 630
E = 685
F = 755
G = 806
A = 890
B = 1000
D5 = 1175
#frequency ranges for each note
'''rangeD4 = range(D4-BANDWIDTH,D4+BANDWIDTH)
rangeE = range(E-BANDWIDTH,E+BANDWIDTH)
rangeF = range(F-BANDWIDTH,F+BANDWIDTH)
rangeG = range(G-BANDWIDTH,G+BANDWIDTH)
rangeA = range(A-BANDWIDTH,A+BANDWIDTH)
rangeB = range(B-BANDWIDTH,B+BANDWIDTH)
rangeD5 = range(D5-BANDWIDTH,D5+BANDWIDTH)'''

