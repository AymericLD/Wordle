# IN104

Ceci est une implémentation du jeu Wordle.

Le programme principal, contenant l'algorithme du jeu est wordle.c.

Les fichiers dico.c et verify.c contiennent les fonctions permettant respectivement de lire et de choisir un mot aléatoire dans un dictionnaire ; et de vérifier si le mot saisi par le joueur se trouve bien dans le dictionnaire.

Les deux dictionnaires utilisés sont fournis : meilleur.txt est le dictionnaire de 286364 mots utilisé pour la vérification de la validité d'un mot, dico.txt est le dictionnaire de 835 mots basiques utilisés pour choisir aléatoirement le mot à deviner.

Instructions de compilation : 

-Compilation du jeu Wordle : 

gcc -Wall -Wfatal-errors -Werror -o wordle.out wordle.c dico.c verify.c

-Compilation de l'IA du jeu Wordle : 

gcc -Wall -Wfatal-errors -Werror -o IA.out IA.c dico.c -lm

Malheureusement, nous ne sommes pas parvenus à corriger l'erreur de segmentation qui apparaît à l'éxécution du programme. Nous y travaillons toujours.


