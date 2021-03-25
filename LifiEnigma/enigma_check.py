#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 25 19:20:56 2021

@author: FL
"""
import time

while True:
    result = input()
    if result=="lifi":
        print("Enigme décodée")
        time.sleep(2)
    else:
        print("Enigme non trouvé")
        time.sleep(2)