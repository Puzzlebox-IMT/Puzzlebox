from piwifi import Scanner, WpaManager
import re



s = Scanner(interface='wlan0', sudo=True)

#Recupère la liste des réseaux et leurs caractéristiques
network_list = s.cells

#Convertit la liste en string
network_list = ' '.join([str(elem) for elem in network_list]) 

print ("*******************************************************************")
print("                          NETWORK LIST                                ")
print ("*******************************************************************\n")


network_list = network_list.split("{")

for each_network in network_list:

     ssid_list = each_network.split(",")
     for each_ssid in ssid_list:

         if re.findall("essid", each_ssid): 

            each_ssid = re.sub("'essid': '", "", each_ssid)
            each_ssid = re.sub("'", "", each_ssid)
            print(each_ssid)

print("\n")
