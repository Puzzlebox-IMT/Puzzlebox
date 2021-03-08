#  <center>-  INSTRUCTIONS DE NAVI  -</center>



### I. MOT DE PASSE CHIFFRÉ ET CLÉ DE CHIFFREMENT

<img src="https://static.thenounproject.com/png/43118-200.png" alt="Password Icons - Download Free Vector Icons | Noun Project" style="zoom:100%;" width="100"/>

Le mot de passe chiffré est un mot hexadécimal de 4 digits généré aléatoirement à chaque lancement de partie (ex : 0568).

La clé de chiffrement est un mot hexadecimal de même taille que le mot de passe chiffré et est présent dans la liste des réseaux WiFi. A vous de le chercher!

### II. CONSEIL POUR RÉUSSIR L'ÉNIGME

<img src="https://upload.wikimedia.org/wikipedia/commons/c/c9/Logic-gate-xor-us.png" alt="File:Logic-gate-xor-us.png - Wikimedia Commons" style="zoom: 100%;" width="150"/>

De nos jours, beaucoup de mécanismes de sécurité utilisent la fonction XOR pour calculer un mot de passe chiffré grâce à une clé. La particularité de cette fonction est qu’elle permet aussi de réaliser l’opération inverse de déchiffrement en calculant le XOR entre la clé de chiffrement ainsi que le mot de passe chiffré. C’est cette opération que les élèves devront réaliser afin de récupérer le mot de passe du WiFi.

À l’aide de cette fiche, vous devrez :

1. Convertir la clé de chiffrement et le code chiffré du réseau Wi-Fi de l’hexadécimal au binaire à l'aide de la table de conversion fournie dans la partie III.

Exemple : Pour le mot héxadécimal 2529 la traduction en binaire est 0010 0101 0010 1001 

<font color="red"> (ATTENTION  : IL EST INDISPENSABLE DE MAINTENIR L'ORDRE DES PAQUETS DE 4 BITS COMME DANS L'EXEMPLE)</font>



2. Effectuer une opération XOR opération XOR entre ces deux suites binaires. Finalement le résultat de l'opération sera convertit en hexadécimal pour obtenir le code du Wifi. (Un exemple est présent dans la partie III)

### III. DOCUMENTS UTILES

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

<center>![](./XOR.png)</center>