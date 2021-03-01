#!/bin/sh

filename=$1

sudo mkdir /home/pi/git_workspace/Puzzlebox/"$filename"
sudo cp /home/pi/git_workspace/Puzzlebox/Common/MQTT/mainWifiEnigma_version_test_mqtt.py /home/pi/git_workspace/Puzzlebox/"$filename"/main_"$filename".py
