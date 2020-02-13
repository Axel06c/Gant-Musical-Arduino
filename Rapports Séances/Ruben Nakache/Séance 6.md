Séance 6:

Lors de cette séance nous nous sommes concentrés sur l'association du software et du hardware, c'est à dire l'association du montage arduino (module Bluetooth, gyromètre/accéléromètre, carte arduino), du gant et de l'application android.

Ainsi nous avons vérifié la fonctionnalité de notre projet de par:

1/La vérification de l'état fonctionnel du gyromètre/accéléromètre

2/La vérification de l'acquisition des valeurs des données obtenues (rythme, volume, doigt/choix du son)

3/La justesse des valeurs obtenues (cohérence avec nos attentes)

4/Le changement des paramètres associés aux sons (volume et son) en fonction du mouvement effectué


1/Pour vérifier l'état du gyromètre/accéléromètre, nous avons fait des tests consistant après avoir enfilé le gant a des mouvements de celui-ci pour vérifier que le gyromètre/accéléromètre nous envoyait les données attendues et qu'il était allumé.
En effet les données reçues, les valeurs du rythme et du volume, correspondaient bien à ce que nous attendions (un entier positif correspondant à une augmentation et un entier négatif correspondant a une diminution).

2/Pour vérifier l'acquisition des valeurs des données obtenues, il a fallu vérifier sur l'application la chaine de caractères reçue par Bluetooth, la chaine de caractères reçue était celle attendue  «%choix du son;volume;rythme;secousse-» .

3/Il a ensuite fallu regarder les valeurs de cette chaine de caractères pour voir si elles étaient en accord avec nos attentes (un chiffre entre 0 et 9 pour le choix du son) or nous avons observé que les valeurs observes ne correspondaient en aucun cas a la valeur du choix associée aux différents doigts. Nous avons donc compris qu'il était nécessaire de brancher les entrées des doigts au 5 Volt et l'entrée du pouce a la masse tout en rajoutant des résistances de 10 kOhm sur chacune des entrées sauf pour celle du pouce afin de reproduire le fonctionnement d'un vrai bouton. 

4/Finalement lors de ces tests décrit  précédemment le volume et le rythme des sons joués en boucle sur l’application android ont évolués comme nous l’attendions, les augmentations lors des mouvement circulaire de gauche à droite et de bas en haut, et les diminutions lors des mouvements circulaires de droite à gauche et de haut en bas .


En conclusion le projet en fonctionnel mais il reste de nombreuses taches à faire :

-Alléger le montage en utilisant un circuit intégré et en soudant les composants

-Créer une boite bracelet pour ranger le circuit intégré

-Coudre les fils sur le gant et l’accéléromètre 

