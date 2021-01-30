#  -  INSTRUCTIONS DE NAVI  -



### MOT DE PASSE CHIFFRÉ

<img src="https://static.thenounproject.com/png/43118-200.png" alt="Password Icons - Download Free Vector Icons | Noun Project" style="zoom:50%;" />

Le mot de passe chiffré que tu devras utiliser est le suivant : **AB12**



### UTILISATION DE LA FONCTION XOR

<img src="https://upload.wikimedia.org/wikipedia/commons/c/c9/Logic-gate-xor-us.png" alt="File:Logic-gate-xor-us.png - Wikimedia Commons" style="zoom: 25%;" />

De nos jours, beaucoup de mécanismes de sécurité utilisent la fonction XOR pour calculer un mot de passe chiffré grâce à une clé. La particularité de cette fonction est qu’elle permet aussi de réaliser l’opération inverse de déchiffrement en calculant le XOR entre la clé de chiffrement ainsi que le mot de passe chiffré. C’est cette opération que les élèves devront réaliser afin de récupérer le mot de passe du WiFi.

À l’aide de cette fiche, vous devrez dans un premier temps convertir la clé de chiffrement et le code chiffré du réseau Wi-Fi de l’hexadécimal au binaire. Vous effectuerez ensuite une opération XOR entre ces deux suites binaires. Finalement le résultat de l'opération sera convertit en hexadécimal pour obtenir le code du Wifi.



### DOCUMENTS UTILES

<u>Table de conversion</u>

| HEXADECIMAL | BINAIRE |
| :---------: | :-----: |
|      0      |  0000   |
|      1      |  0001   |
|      2      |  0010   |
|      3      |  0011   |
|      4      |  0100   |
|      5      |  0101   |
|      6      |  0110   |
|      7      |  0111   |
|      8      |  1000   |
|      9      |  1001   |
|      A      |  1010   |
|      B      |  1011   |
|      C      |  1100   |
|      D      |  1101   |
|      E      |  1110   |
|      F      |  1111   |



<u>Table de vérité</u>

|  A   |  B   | Solution |
| :--: | :--: | :------: |
|  0   |  0   |    0     |
|  0   |  1   |    1     |
|  1   |  0   |    1     |
|  1   |  1   |    0     |

Exemple d'utilisation :

​                 1 0 0 1 

XOR         1 0 1 0

-----------------------------

​                0 0 1 1