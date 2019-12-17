Séance 2:
Le but de cette séance fut la prise en main de l’accéléromètre Gy-521 couplé à la puce MPU-6050.

Tout d'abord j'ai dû comprendre ce qu'est un accéléromètre, j'ai donc appris que c'est un condensateur utilisé comme un capteur.

Puis j'ai dû comprendre le programme arduino permettant de régler/calibrer la puce MPU-6050, en effet pour utiliser l'accéléromètre il faut 
réveiller la puce MPU-6050 afin que celle-ci communique avec l'accéléromètre.

Ensuite il a fallu appréhender le système de récupération des octets qui utilise des opérateurs logiques pour récupérer 2 registres de 8 bits 
c'est a dire 2 octets que j'ai stocké dans 3 variables accélération (1 selon chaque axe).

Il ne faut pas oublier le système de gamme qui nous permet de choisir la précision des valeurs renvoyées par l'accéléromètre, j'ai choisi la 
gamme la moins précise +-2G puisque lorsque je fais le mouvement de l'accéléromètre (donc du gant fictif) de haut en bas,
j'atteints une accélération maximale quasi identique a celle d'un objet qui tombe lâché a une vitesse et une accélération nulles.

Lors de premiers tests "basique" consistant à faire des mouvements simples selon 1 seul axe j'ai rencontré un problème, l'accélération prenait
les valeurs -1, 0 ou 1 peut importe l'axe choisit, le problème venait de la division de l'accélération par le coefficient de la gamme choisie 
ici 16384.0 que j'avais écrit 16384,0 , j'ai donc remplacer la virgule par le point pour signifier que ce nombre est un décimal.

Enfin j'ai effectué des tests avec l'accéléromètre ceux-ci consistant à enregistrer les valeurs de l'accélération (avec le logiciel terminal)
selon l'axe X, selon l'axe Y et selon l'axe z tout en effectuant des mouvements différents pour chaque test:
Test 1: Mouvement horizontal puis selon, x selon y et selon z
[Test1](https://github.com/Axel06c/Gant-Musical-Arduino/blob/master/lib/Images/Test1.png)
Test 2: Mouvement horizontal, puis Mouvement vertical et Horizontal
Test 3: Mouvement horizontal, puis Mouvement vertical, Horizontal et Vertical avec une inclinaison 1
Test 4: Mouvement horizontal, puis Mouvement vertical et Horizontal et Vertical avec une inclinaison 2
Test 5: Mouvement horizontal, puis Mouvement vertical et Horizontal et Vertical avec mouvement "parasite"1 (rotation)
Test 6: Mouvement horizontal, puis Mouvement vertical et Horizontal et Vertical avec mouvement "parasite"2 (rotation)
Ainsi j'ai observé la nécessité d'un calibrage afin d'utiliser l'accéléromètre.
