#Tone detection shamelessly stolen from:
#https://benchodroff.com/2017/02/18/using-a-raspberry-pi-with-a-microphone-to-hear-an-audio-alarm-using-fft-in-python/
#!/usr/bin/env python
import pyaudio
from numpy import *
from scipy import fft
from time import sleep
from collections import deque
import paho.mqtt.client as mqtt
import requests
import pygame.mixer
from pygame.mixer import Sound
import RPi.GPIO as GPIO
from ctypes import *
from contextlib import contextmanager


ERROR_HANDLER_FUNC = CFUNCTYPE(None, c_char_p, c_int, c_char_p, c_int, c_char_p)

def py_error_handler(filename, line, function, err, fmt):
    pass

c_error_handler = ERROR_HANDLER_FUNC(py_error_handler)

@contextmanager
def noalsaerr():
    asound = cdll.LoadLibrary('libasound.so')
    asound.snd_lib_error_set_handler(c_error_handler)
    yield
    asound.snd_lib_error_set_handler(None)


def musicalNoteDetection():
    
    

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
    confirm = Sound("Music/OOT_Song_Correct.wav") #change accordingly for your song confirmation sound file name/location

    #mqtt stuff
    client = mqtt.Client()
    client.connect("localhost",1883,300)
    client.subscribe("WifiEnigma/#")
    
    client.loop_start()
    
    

    #Volume Sensitivity, 0.05: Extremely Sensitive, may give false alarms
    #             0.1: Probably Ideal volume
    #             1: Poorly sensitive, will only go off for relatively loud
    SENSITIVITY= 1.0

    #Bandwidth for detection (i.e., detect frequencies within this margin of error of the TONE)
    BANDWIDTH = 25

    # Alarm frequencies (Hz) to detect (Use audacity to record a wave and then do Analyze->Plot Spectrum)
    C = 494
    D4 = 542
    E = 618
    F = 660
    G = 744
    A = 882
    B = 992
    D5 = 1179
    #frequency ranges for each note
    '''rangeD4 = range(D4-BANDWIDTH,D4+BANDWIDTH)
    rangeE = range(E-BANDWIDTH,E+BANDWIDTH)
    rangeF = range(F-BANDWIDTH,F+BANDWIDTH)
    rangeG = range(G-BANDWIDTH,G+BANDWIDTH)
    rangeA = range(A-BANDWIDTH,A+BANDWIDTH)
    rangeB = range(B-BANDWIDTH,B+BANDWIDTH)
    rangeD5 = range(D5-BANDWIDTH,D5+BANDWIDTH)'''


    #These numbers work for my ocarina in my house with a blue yeti, ymmv
    minC = C-25
    maxC= C+25
    minD4 = D4-25
    maxD4 = D4+25
    minE = E-25
    maxE = E+25
    minF = F-25
    maxF = F+25
    minG = G-BANDWIDTH
    maxG = G+BANDWIDTH
    minA = A-BANDWIDTH
    maxA = A+55
    minB = B-BANDWIDTH
    maxB = B+BANDWIDTH
    minD5 = D5-BANDWIDTH
    maxD5 = D5+BANDWIDTH

    # Song note sequences
    sun = deque(['A','F','D5','A','F','D5'])
    time = deque(['A','D4','F','A','D4','F'])
    storm = deque(['D4','F','D5','D4','F','D5'])
    forest = deque(['D4','D5','B','A','B','A'])
    saria = deque(['F','A','B','F','A','B'])
    fire = deque(['F','D4','F','D4','A','F']) #This is just 6 notes, play all 8 if you want ;)
    epona = deque(['D5','B','A','D5','B','A'])
    zelda = deque(['E','G','D4','E','G','D4'])
    heal = deque(['B','A','F','B','A','F'])
    test = deque(['C','D4','E','F','G','F']) #Not a Zelda song, just nice to make sure everything's working
    #heard note sequence deque
    notes = deque(['G','G','G','G','G','G'], maxlen=6)



    # Show the most intense frequency detected (useful for configuration)
    frequencyoutput=True
    freqNow = 1.0
    freqPast = 1.0

    #Set up audio sampler - 
    NUM_SAMPLES = 2048
    SAMPLING_RATE = 48000 #make sure this matches the sampling rate of your mic!
    with noalsaerr():
       pa = pyaudio.PyAudio()
    _stream = pa.open(format=pyaudio.paInt16,
                      channels=1, rate=SAMPLING_RATE,
                      input=True,
                      frames_per_buffer=NUM_SAMPLES)



    #print("Alarm detector working. Press CTRL-C to quit.")

    while True:
        while _stream.get_read_available()< NUM_SAMPLES: sleep(0.01) #Retourne le nombre d'image qui peuvent etre lue sans attendre
        audio_data  = frombuffer(_stream.read(
        _stream.get_read_available()), dtype=short)[-NUM_SAMPLES:]
        # Each data point is a signed 16 bit number, so we can normalize by dividing 32*1024
        normalized_data = audio_data / 32768.0
        #print(type(NUM_SAMPLES))
        #print("La taille du tableau audio est :", +audio_data.size)
        #print("Le tableau de audio est :\n", +audio_data)
        #print("Le tableau de normalized est :\n", +normalized_data)
        #print("La taille du tableau normalise est :", +normalized_data)
        intensity = abs(fft.fft(normalized_data))[:int(NUM_SAMPLES//2)]
        frequencies = linspace(0.0, float(SAMPLING_RATE)//2, num=NUM_SAMPLES//2)
        if frequencyoutput:
           which = intensity[1:].argmax()+1
           # use quadratic interpolation around the max
           if which != len(intensity)-1:
              y0,y1,y2 = log(intensity[which-1:which+2:])
              x1 = (y2 - y0) * .5 / (2 * y1 - y2 - y0)
              # find the frequency and output it
              freqPast = freqNow
              freqNow = (which+x1)*SAMPLING_RATE/NUM_SAMPLES
           else:
              freqNow = which*SAMPLING_RATE/NUM_SAMPLES
           # print "\t\t\t\tfreq=",freqNow,"\t",freqPast
        if minC <= freqPast <= maxD5 and abs(freqNow-freqPast) <= 25:
           if minA<=freqPast<=maxA and minA<=freqNow<=maxA and notes[-1]!='A':
              notes.append('A') #La note A (La) est ajoutée au tableau de note
              GPIO.output(26, GPIO.LOW) #LED éteinte
              GPIO.output(19, GPIO.LOW)
              GPIO.output(13, GPIO.HIGH) #LED allumée
              GPIO.output(6, GPIO.LOW)
              GPIO.output(5, GPIO.LOW)
              print ("You played A!")
           elif minF<=freqPast<=maxF and minF<=freqNow<=maxF and notes[-1]!='F':
              notes.append('F')
              GPIO.output(26, GPIO.LOW)
              GPIO.output(19, GPIO.LOW)
              GPIO.output(13, GPIO.LOW)
              GPIO.output(6, GPIO.HIGH)
              GPIO.output(5, GPIO.LOW)
              print ("You played F!")
           elif freqPast <= maxD4 and minD4 <= freqNow <= maxD4 and notes[-1]!='D4':
              notes.append('D4')
              GPIO.output(26, GPIO.LOW)
              GPIO.output(19, GPIO.LOW)
              GPIO.output(13, GPIO.LOW)
              GPIO.output(6, GPIO.LOW)
              GPIO.output(5, GPIO.HIGH)
              print ("You played D4!")
           elif minD5 <= freqPast <= maxD5 and minD5 <= freqNow <= maxD5 and notes[-1]!='D5':
              notes.append('D5')
              GPIO.output(26, GPIO.LOW)
              GPIO.output(19, GPIO.HIGH)
              GPIO.output(13, GPIO.LOW)
              GPIO.output(6, GPIO.LOW)
              GPIO.output(5, GPIO.LOW)
              print ("You played D5!")
           elif minB<=freqPast<=maxB and minB<=freqNow<=maxB and notes[-1]!='B':
              notes.append('B')
              GPIO.output(26, GPIO.HIGH)
              GPIO.output(19, GPIO.LOW)
              GPIO.output(13, GPIO.LOW)
              GPIO.output(6, GPIO.LOW)
              GPIO.output(5, GPIO.LOW)
              print ("You played B!")
           elif minE<=freqPast<=maxE and minE<=freqNow<=maxE and notes[-1]!='E':
              notes.append('E')
              GPIO.output(26, GPIO.HIGH)
              GPIO.output(19, GPIO.LOW)
              GPIO.output(13, GPIO.LOW)
              GPIO.output(6, GPIO.LOW)
              GPIO.output(5, GPIO.LOW)
              print ("You played E!")
           elif minG<=freqPast<=maxG and minG<=freqNow<=maxG and notes[-1]!='G':
              notes.append('G')
              GPIO.output(26, GPIO.LOW)
              GPIO.output(19, GPIO.HIGH)
              GPIO.output(13, GPIO.LOW)
              GPIO.output(6, GPIO.LOW)
              GPIO.output(5, GPIO.LOW)
              print ("You played G!")
              
                     
           elif minC<=freqPast<=maxC and minC<=freqNow<=maxC and notes[-1]!='C':
              notes.append('C')
              GPIO.output(26, GPIO.LOW)
              GPIO.output(19, GPIO.HIGH)
              GPIO.output(13, GPIO.LOW)
              GPIO.output(6, GPIO.LOW)
              GPIO.output(5, GPIO.LOW)
              print ("You played C!")
           else:
              print ("What the heck is that?") #prints when sound is in range but not identifiable as note
											#or when a note has already been registered and is "heard" again

        if notes==sun:
           print ("Sun song")
           confirm.play()
           notes.append('G') #append with 'G' to 'reset' notes, this keeps the song from triggering constantly
        if notes==forest:
           print ("Minuet of Forest!")
           client.publish("songID", "4") #4=Forest
           confirm.play()
           notes.append('G')
        if notes==test:
           print ("Musique de test reconnue !")
           client.publish("WifiEnigma/song", "TestSong") #4=Forest 
           confirm.play()
           notes.append('G')


if (__name__ == '__main__'):

   musicalNoteDetection()
