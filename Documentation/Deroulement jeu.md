
## Déroulement d'une partie
On part du principe qu'on a un socle où peuvent se placer les faces à n'importe quel endroit grâce à une connectique standardisée. Le socle dispose d'une partie centrale avec un bouton permettant d'initialiser une partie.

Chaque face correspond à un code couleur. Il est possible de choisir les faces avec lesquelles utilisées lors de la partie en appuyant sur les boutons de validation des faces. Si le bouton de validation d'une face est pressé et qu'ensuite le joueur initie une partie, la face sera comprise dans cette partie. 
Il est important de placer ces faces sur le socle avant une partie puis de réaliser un appui long sur le bouton de démarrage pour lancer une partie. Dès lors on peut résoudre les énigmes liées à ces faces, soit en les laissant sur le socle, ou alors en les détachant. Une fois qu'on juge chaque face résolue, on peut replacer les faces sur le socle et appuyer brièvement sur le bouton "Terminer" pour que le système vérifie si toutes nos faces sont bien résolues. Le cas échéant un message indique aux joueurs qu'ils ont gagné et les faces sont ensuite réinitialisées automatiquement (retour à l'état non résolu et réinitilisation de certains éléments dans le code/ou physiques de la face). Par contre s'il manque des faces sur le socle parmi celles utilisées pour lancer la partie, un message va demander de bien vouloir placer toutes les faces de la partie en cours sur le socle et de réappuyer sur le bouton pour vérification. D'autre part, si toutes les faces sont présentes mais qu'une ou plusieurs ne sont pas résolues, le système va indiquer, dans un message, de résoudre les faces non résolues.

À tout moment on peut faire un appui long sur le bouton pour arrêter le jeu et réinitialiser les faces

​		










```mermaid
graph TB;
A[Appui  bouton central]-->W{Appui long ou court ?}
W-- court-->Y;
W-- long, réinitialisation du jeu -->L
Y{est-on dans une partie ?}
Y-- oui, vérification de la résolution des faces -->F
Y-- non, début d'une partie -->B
B{Y'a-t-il des faces en place sur le socle ? };
B-- oui -->C
B-- non -->X[message 'placer des faces sur le socle pour débuter une partie']
X-->A
C(Lancement d'une partie avec ces faces)
C-.résolution des faces, sur le socle ou bien enlevées.->D(Remise en place des faces sur le socle si énigmes jugées résolues, pour vérification)
D-->E[appui bouton central pour vérifier que les énigmes ont été résolues]
E-->F{Toutes les faces du jeu en cours présentes sur le socle?}
F-- oui -->H{Toutes les faces sont à l'état résolu ?}
F-- non -->I[message : 'faces manquantes']
I-- placer les faces manquantes -->E
H-- oui -->K[Message 'Toutes les énigmes ont été résolues, gagné !']
K-->L[Arrêt du jeu ]
L-->AA[Réinitialisation des faces]
H--non-->M[Message 'des énigmes ne sont pas résolues']
M-- résoudre les énigmes non résolues-->E
```

