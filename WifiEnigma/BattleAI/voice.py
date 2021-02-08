import os
import time

def synthetize_voice(message):

    print('Pico Text to Speech')
    os.system('pico2wave -l  fr-FR -w voice.wav "' + message + '" && aplay voice.wav')
    time.sleep(1)

def delete_wav():

    os.system('sudo rm -rf voice.wav')


if __name__ == '__main__':

   message = "Test"
   synthetize_voice(message)
