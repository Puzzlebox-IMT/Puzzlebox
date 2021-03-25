#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 25 21:39:31 2021

@author: FL
"""

from gpiozero import MCP3008
from time import sleep
import os
import time

pot = MCP3008(0)
pot_stay = 0

while True:
    pot_changed = True
    if (pot_stay==pot.value):
        pot_changed = False
    else:
        print (pot)
        volume = pot
        volume = round(volume)
        volume = int(volume)
        print('Volume = {volume}%' .format(volume = volume))
        volume_cmd = 'sudo amixer cset numid=1 -- {volume}% > /dev/null' .format(volume = volume)
        os.system(volume_cmd)
        pot_stay = pot
        time.sleep(1)