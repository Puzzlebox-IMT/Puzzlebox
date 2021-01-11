from piwifi import Scanner, WpaManager
import wifi
import re


def scan_wifi1():

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



def scan_wifi2():
    network_list = []

    cells = wifi.Cell.all('wlan0')

    for cell in cells:
        network_list.append(cell)

    #Convertit la liste en string
    network_list = ' '.join([str(elem) for elem in network_list])

    print ("*******************************************************************")
    print("                          NETWORK LIST                                ")
    print ("*******************************************************************\n")

    network_list = network_list.split("Cell(ssid=")

    parsed_list = []
    for each_network in network_list:

        each_network = re.sub("\)", "", each_network)
        parsed_list.append(each_network)

    return parsed_list


def Search():
    wifilist = []

    cells = wifi.Cell.all('wlan0')

    for cell in cells:
        wifilist.append(cell)

    return wifilist


def Add(cell, password=None):
    if not cell:
        return False

    scheme = wifi.Scheme.for_cell('wlan0', cell.ssid, cell, password)
    scheme.save()
    return scheme


def Delete(ssid):
    if not ssid:
        return False


def FindFromSearchList(ssid):
    wifilist = Search()

    for cell in wifilist:
        if cell.ssid == ssid:
            return cell

    return False



def FindFromSavedList(ssid):
    cell = wifi.Scheme.find('wlan0', ssid)

    if cell:
        return cell

    return False


def Connect(ssid, password=None):
    cell = FindFromSearchList(ssid)

    if cell:
        savedcell = FindFromSavedList(cell.ssid)

        # Already Saved from Setting
        if savedcell:
            savedcell.activate()
            return cell

        # First time to conenct
        else:
            if cell.encrypted:
                if password:
                    scheme = Add(cell, password)

                    try:
                        scheme.activate()

                    # Wrong Password
                    except wifi.exceptions.ConnectionError:
                        Delete(ssid)
                        return False

                    return cell
                else:
                    return False
            else:
                scheme = Add(cell)

                try:
                    scheme.activate()
                except wifi.exceptions.ConnectionError:
                    Delete(ssid)
                    return False

                return cell

    return False




ssid_list = scan_wifi2()
print(ssid_list)
