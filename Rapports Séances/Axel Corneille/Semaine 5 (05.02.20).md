Aujourd'hui avec Ruben nous avons enfin trouvé une chaine de caractères correcte a utiliser dans nos tranferts de données.
J'ai adapté mon code pour pouvoir recevoir correctement les données.

Concrètement, l'acceleromètre va créer une valeur en fonction de l'orientation horizontale ou verticale prise. 
Il y a également une fonction pouvant nous indiquez si on secoue la main.

La chaine de données est de la forme: "%1;20;10;0-"
                                        || |  | ||
Premier terme qui permet a             / | |  | | \         Dernier terme qui permet a 
l'application de détecter le début ___/  | |  | |  \_______ l'application de détecter la fin
de réception de données à traiter        | |  | |           de réception des données a traiter
                                         | |  | |
      1er chiffre: indique              /  |  |  \       4ème chiffre indique la valeur
      quel doigt est appuyé  __________/   |  |   \_____ Attribuée a la secousse
      (aucuns,1,2,etc)                     |  |          (1 si secoué, 0 sinon)
                                           |  |
             2ème chiffre: indique        /    \      3ème chiffre: indique
             la valeur attribuée au  ____/      \____ la valeur attribuée au
             volume                                   tempo

pour le volume et le tempo, j'ai choisi demandé a Ruben a ce que l'acceléromètre 
