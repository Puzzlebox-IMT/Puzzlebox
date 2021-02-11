#                             DEPENDENCIES



#### 1) PYAUDIO

`sudo pip3 install pyaudio



#### 2) SCIPY

```py
sudo pip3 install scipy
```





#### 3) PAHO MQTT

```
sudo apt-get install -y mosquitto mosquitto-clients
sudo pip3 install paho-mqtt
```



#### 4) SCANNER WIFI

```
sudo pip3 install wifi
```



#### 5) SVOX

```
sudo pip3 install py-picotts
sudo apt-get install -y ffmpeg
sudo wget http://ftp.fr.debian.org/debian/pool/non-free/s/svox/libttspico-utils_1.0+git20130326-9_armhf.deb
sudo wget http://ftp.fr.debian.org/debian/pool/non-free/s/svox/libttspico0_1.0+git20130326-9_armhf.deb
sudo wget http://ftp.fr.debian.org/debian/pool/non-free/s/svox/libttspico-data_1.0+git20130326-9_all.deb
sudo dpkg -i libttspico-data_1.0+git20130326-9_all.deb
sudo dpkg -i libttspico-utils_1.0+git20130326-9_armhf.deb
sudo dpkg -i libttspico0_1.0+git20130326-9_armhf.deb
```



#### 5) CONFIGURER LE MICRO ET LE HAUT PARLEUR 



https://www.pofilo.fr/post/20181216-mic-raspberry-pi/

```
aplay -l
```

```
arecord -l
```



#### 6) CORRIGER LES BUGS LIES A ALSA 

sudo apt-get install libasound-dev



Dans le fichier  /usr/share/alsa/alsa.conf commenter les lignes suivantes : 



#pcm.rear cards.pcm.rear
#pcm.center_lfe cards.pcm.center_lfe
#pcm.side cards.pcm.side

#pcm.hdmi cards.pcm.hdmi

#pcm.modem cards.pcm.modem
#pcm.phoneline cards.pcm.phoneline



https://stackoverflow.com/questions/7088672/pyaudio-working-but-spits-out-error-messages-each-time

```py
from ctypes import *
from contextlib import contextmanager
import pyaudio

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
```

After doing this you can re-use the error handler by using the `noalsaerr` context:

```py
with noalsaerr():
    p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.paFloat32, channels=1, rate=44100, output=1)
...
```



D'après cet article les erreur concernant le jack ne sont pas bloquantes :

https://java.wekeepcoding.com/article/12298609/PyAudio+warnings+poluting+output



**Remplacer la ligne :**

audio_data  = fromstring(_stream.read(_stream.get_read_available()), dtype=short)[-NUM_SAMPLES:]

**Par la ligne (+ajouter frombuffer aux appels de fonctions python):**

audio_data  = frombuffer(_stream.read(_stream.get_read_available()), dtype=short)[-NUM_SAMPLES:]





**Remplacer la ligne :**

intensity = abs(fft(normalized_data))[:NUM_SAMPLES/2]

**Par la ligne (+ajouter frombuffer aux appels de fonctions python):**

intensity = abs(fft.fft(normalized_data))[:NUM_SAMPLES/2]

