Aujourd'hui avec Ruben nous avons enfin trouvé une chaine de caractères correcte a utiliser dans nos tranferts de données.
J'ai adapté mon code pour pouvoir recevoir correctement les données.

Concrètement, l'acceleromètre va créer une valeur en fonction de l'orientation horizontale ou verticale prise. 
Il y a également une fonction pouvant nous indiquez si on secoue la main.

La chaine de données est de la forme: "%1;20;10;0-"  

Premier terme (%) permet a l'application de détecter le début de réception de données à traiter         
Dernier terme (-)permet a l'application de détecter la fin  de réception des données a traiter                                
1er chiffre: indique quel doigt est appuyé  (aucuns,1,2,etc)
2ème chiffre: indique  la valeur attribuée au volume   
3ème chiffre: indique  la valeur attribuée au tempo
4ème chiffre indique la valeur ettribuée a la secousse (1 si secoué, 0 sinon)  



Pour le volume et le tempo, j'ai choisi de demander a Ruben a ce que l'acceléromètre envoie en continue les valeurs sans leur donner de maximum ou minmum.

Pour le traitement, mon code sépare les différents chiffres et compare les valeurs de l'envoie d'avant avec le dernier.
Si les valeurs sont supérieures au valeurs précédentes, alors on incrémente le son, et inversement.
Cela permet de mieux se calibrer dans l'espace.

Pour la semaine prochaine il me faut implémenter quand on ne touche aucuns doigts, faire en sorte que le compteur se remet a zéro et se calibre a nouveau quand on rappuie sur les doigts.
