Durant cette semaine, Ruben as avancé de son coté le montage, et j'ai paufiné mon application, pour pouvoir enfin tester si tout marchait
 comme l'on voulait.  
 
Et malheureusement non, les doigts n'étaient pas détectés quand on appuyait dessus.
Nous avons fini par trouver que notre montage n'était pas bien optimisé... Le but des plaques de cuivre sur les doigts etait de simuler un bouton, et nous avions prevus 
de verifier si le courant passait ou pas en reliant seulement du 5V-->pouce | doigt-->input.
il a donc fallu que l'on modifie notre circuit électrique en rajoutant une résistance et faisant passer le 5V dans les doigt (avec l'input et la résistance au milieu), et le pouce a la masse pour pouvoir récuperer 0 si appuyé, 1 sinon.  

De mon coté, j'ai du et je dois énormément débugguer mon application, j'ai pu déjà faire fonctionner la sélection de pack de son, puis ai réussi a intégrer 3 sons de plus.
J'ai commencé a réflechir a un moyen de pouvoir synchroniser les sons entre eux pour ne pas créer de cacophonie, puis également a récuperer des sons de bonne qualités, musicalement beaux, de même durée, de même tempo, pour avoir une bonne concordance de tout ce qu'on entend.  

Mon but est vraiment de trouver un moyen de proposer une expérience de musique jolie a écouter.
