Aujourd'hui avec Ruben nous avons enfin trouvé une chaine de caractères correcte a utiliser dans nos tranferts de données.
J'ai adapté mon code pour pouvoir recevoir correctement les données.

Concrètement, l'acceleromètre va créer une valeur en fonction de l'orientation horizontale ou verticale prise. 
Il y a également une fonction pouvant nous indiquez si on secoue la main.

La chaine de données est de la forme: "%1;20;10;0-"\n
                                        || |  | ||\n
Premier terme qui permet a             / | |  | | \         Dernier terme qui permet a\n
l'application de détecter le début ___/  | |  | |  \_______ l'application de détecter la fin\n
de réception de données à traiter        | |  | |           de réception des données a traiter\n
                                         | |  | |\n
      1er chiffre: indique              /  |  |  \       4ème chiffre indique la valeur\n
      quel doigt est appuyé  __________/   |  |   \_____ Attribuée a la secousse\n
      (aucuns,1,2,etc)                     |  |          (1 si secoué, 0 sinon)\n
                                           |  |\n
             2ème chiffre: indique        /    \      3ème chiffre: indique\n
             la valeur attribuée au  ____/      \____ la valeur attribuée au\n
             volume                                   tempo\n
\n
pour le volume et le tempo, j'ai choisi demandé a Ruben a ce que l'acceléromètre 
