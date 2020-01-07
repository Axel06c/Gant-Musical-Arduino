Séance 3 (séance du 06/01/20):

1/Calibration:

Nous avons vu précédemment qu'une calibration de l'accéléromètre/gyromètre est nécessaire afin de l'utiliser. Ainsi pour calibrer l'accéléromètre nous avons construit un support en bois avec des rapporteurs qui à l'aide de mesure selon les axes x,y et z nous a permis de déterminer les biais et gain de chaque axe de mesure, ainsi que les erreurs angulaires de positionnement des axes. Pour cela on va mesurer la gravité (normalement  -1 sur l’axe considéré, et 0 sur les autres), en positionnant le capteur suivant la verticale pour chaque axe et en le maintenant immobile (pas d'accélération parasite) puis en cherchant minimum et maximum. 

Cela a permis d’obtenir un facteur a de gain, et un facteur b d’offset par axe qui nous donne la valeur calibrée Vc à partir de la mesure Vm:
 	
  Vc = a* Vm +b.

Pour les erreurs angulaires, on a pu constater qu’il n’est pas nécessaire de les prendre en compte.

![Montage avec rapporteurs + Arduino nano et accéléromètre/gyromètre](https://github.com/Axel06c/Gant-Musical-Arduino/blob/master/lib/Images/montage%20calibrage.jpg)





2/Matrice de Rotation

Le référentiel du senseur est lié au Gant, et change suivant la position de la main. Pour avoir une mesure d’accélération (A) et de vitesse angulaire (V) dans un référentiel absolu (terrestre), il faut corriger cette rotation, qui est donnée par la matrice de rotation M.

Vm = M * (Vreel)

Am = M * (Areel + Agravité)

On peut mesurer cette matrice de rotation Am = M * Agravité  lorsque que le gant est immobile, c’est-à-dire lorsque la norme de l’accélération est égale à la norme de la gravité : ||Am|| = 1.

En  prenant les conventions d’Euler (https://fr.wikipedia.org/wiki/Angles_d%27Euler), on obtient les 3 équations avec Psi rotation autour de Z, puis Téta rotation autour de X, puis Phi rotation autour de Z :

-sin(téta) * sin(psi) =  Xacc 

Cos(psi) * sin(teta) = Yacc

-Cos(téta) = Zacc

On peut constater une incertitude sur phi, impossible à mesurer car phi est dans une rotation autour de l’axe de la gravité. On prendra donc phi =0.

On calculera cette matrice de rotation à chaque fois que le gant est immobile, et on utilisera cette nouvelle matrice ou la dernière calculée pour avoir la mesure d’accélération et de vitesse dans le référentiel terrestre, en appliquant la matrice inverse :

Areel = M-1  *Am – A gravité

Vreel = M^(-1)  * Vm

Et M^(-1) obtenu en appliquant des rotations avec -Phi autour de Z, puis -Téta rotation autour de X, puis -Psi rotation autour de Z.

3/Détection de mouvement et Filtre optimisant

Pour notre Musicano, il faut mesurer la position angulaire du gant suivant la vertical et suivant un axe horizontal.

Dans un premier temps on a essayé d’utiliser l’accéléromètre pour détecter des mouvements rectiligne. Mais cela n’a pas été concluant (information multiples sur les axes).

On utilise donc le Gyromètre en faisant des mouvements angulaires/circulaires et non des mouvements rectilignes et en intégrant sa mesure dans le temps. Pour éviter les parasites on utilise une moyenne glissante de 9 points (suffisante).

Puis un seuil angulaire de quelques degrés permet de définir des incréments de rotation angulaire du gant pris en compte par le logiciel Android.

On peut aussi détecter un choc (accélération >2G) qui donne une information supplémentaire.

![Mouvement du Gant sur X et Y](https://github.com/Axel06c/Gant-Musical-Arduino/blob/master/lib/Images/mouvement%20circulaire%20gauche%20a%20droite2.png)   
![Mouvement du Gant sur Z](https://github.com/Axel06c/Gant-Musical-Arduino/blob/master/lib/Images/mouvement%20circulairehaut%20bas.png)

4/ Connexion avec l’application Android

Les informations de Volume (incrément suivant Z) et de Rythme (incrément suivant X et Y), la détection de choc et les contacts entre pouce et doigts du gant sont envoyés par Bluetooth en boucle à l’application Android.
 
5/Montage

Enfin nous avons commencé le montage du gant pour cela nous avons pris un gant droit sur lequel nous avons collé des fils de cuivres, du scotch double face et du scotch de cuivre.

![Gant dessus](https://github.com/Axel06c/Gant-Musical-Arduino/blob/master/lib/Images/Gant%20fils.jpg) ![Gant paume](https://github.com/Axel06c/Gant-Musical-Arduino/blob/master/lib/Images/Gant%20cuivre.jpg)

Les fils connecté aux PIN d’entrée de  l’Arduino permettent de détecter le contact entre le pouce (connecté au 5V) et un doigt.


![Montage Musicano](https://github.com/Axel06c/Gant-Musical-Arduino/blob/master/lib/Images/Musicano%20montage.jpg)
