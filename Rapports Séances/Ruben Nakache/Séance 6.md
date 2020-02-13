Séance 6:

Lors de cette séance nous nous sommes concentrés sur l'association du software et de l'hardwware, c'est a dire l'association du montage arduino (module bluetooth, gyrometre/accelerometre,carte arduino), du gant et de l'application android.

Ainsi nous avons verifié la fonctionnalité de notre projet de par:
-La verification de l'etat fonctionnel du gyrometre/accelerometre
-La verification de l'acquisation des valeurs des données obtenues(rythme,volume, doigt/choix du son)
-La justesse des valeurs obtenues (coherence avec nos attentes)
-Le changement des parametres associés aux son (volume et son) en fonction du mouvement effectué

Pour verifier l'etat du gyrometre/accelerometre, nous avons fait des tests consistant apres avoir enfilé le gant a des mouvements de celui ci pour verifier que le gyrometre/accelerometre nous envoyait les données attendues et qu'il était allumé.
En effet les données recues, les valeurs du rythme et du volume, correspondaient bien a ce que nous attendions (une entier positif correspondant a une augmentaton et un entier negatif correspondant a une diminution).

Pour verifier l'acquisation des valeurs des données obtenues, il a fallu verifier sur l'application la chaine de caracteres recue par Bluetooth, la chaine de caractere recue etait celle atendue.

Il a ensuite fallu regarderles valeurs de cette chaine de caracteres pour voir si elles etaient en accord avec nos attentes (un chiffre entre 0 et 9 pour le choix du son) or nous avons observé que les valeurs observes ne correpondaient en aucun cas a la valeur du choix associée aux differents doigts. Nous avons donc compris qu'il etait necessaire de brancher les entrées des doigts au 5 Volt et l'entrée du pouce a la masse tout en rajoutant des resistances de 10 kOhm sur chacune des entrées sauf pour celle du pouce afin de reproduire le fonctionnment d'un vrai bouton.
