Nous avons finalisé la connexion Bluetooth entre la carte arduino à l'aide du module Bluetooth et avec le téléphone à l'aide de  l'application Android. 
Pour se faire nous avons envoyé des chaines de données "%choix du son;volume;rythme;secousse-", mesurées à l'aide du gyroscope/accéléromètre,  par le module Bluetooth au téléphone et nous attendions un changement de volume et de rythme pour le son choisi par l'utilisateur (ici nous).
Nous avons bien obtenu le changement attendu correspondant à une augmentation ou une diminution du volume et/ou du rythme du son.



Nous avons aussi avancé le montage du Gant, nous nous sommes rendus compte que l'utilisation des fils de cuivre entre le montage arduino était une mauvaise idée en effet ces fils de cuivre étant peu résistant, ils ne supporteraient pas les mouvements amples du gant.
Ainsi nous les avons remplacé par des fils plus résistants, moins longs et "collés" entre eux de façon a épurer le montage, il a ensuite fallu dénuder ces fils pour les souder a des câbles males et femelles ainsi qu'a des connecteurs males afin de les placer sur la plaque.

![Gant + Montage arduino du Musiacano](https://github.com/Axel06c/Gant-Musical-Arduino/blob/master/lib/Images/Gant%202%20%2BMontage%20arduino.jpg)

![Gant du Musicano](https://github.com/Axel06c/Gant-Musical-Arduino/blob/master/lib/Images/Gant%202.jpg)

Les câbles femelles sont destinés au branchement du Gyroscope/accéléromètre afin que les mesures soient bien effectuées sur le gant.
Il nous faut trouver un moyen de bloquer le gyroscope/accéléromètre sur le gant de façon à ce que l'axe z soit bien dirigé vers le bas.

Nous avons également vérifié l'efficacité des fils grâce à un voltmètre, nous placions la masse sur un bout du fil et le 5volt sur l'autre bout et nous vérifions ainsi le passage du courant dans les fils.

L'objectif suivant est de fabriquer une petite boite bracelet à poser sur le poignet contenant le montage avec la carte arduino ainsi que la batterie.
