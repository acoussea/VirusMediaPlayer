# Projet conception pratique d'un virus
## Contexte 
On vous fourni un cd Rom rempli d'images et de vidéos accompagné d'un programme s'intitulant MediaPlayer.exe (le virus) censé n'afficher qu'une image (mais en réalité plus que cela...).
Ici, c'est la proximité d'un "Player" à côté de multiples images qui permet de susciter le click de l'utilisateur, et donc la diffusion.

Le virus a construire est un virus de type compagnon.
L'utilisateur cible est un utilisateur moyennement sensibilisé à la sécurité informatique, possédant une connaissance moyenne d'un système d'exploitation. Autrement dit, il connait les règles de sécurité mais ne les applique que très rarement.

Environnement de travail : OS Linux, Langage C, compilateur GCC



#### Principe d'un Virus Compagnon
Forme de réplication des virus qui volent l'identité (le nom) et le lieu de résidence d'un fichier existant original (exécutable) qui sera pris pour cible. Lorsque l'utilisateur croit lancer l'un de ses programmes il lance en réalité le virus qui s'exécute, assurant ainsi sa propagation, puis c'est le virus lui-même qui lance le programme demandé afin d'éviter les soupçons de l'utilisateur.   
Ces virus ne sont donc pas destructeurs (dans leur méthode d'implantation - ce qui ne préjuge pas de leur charge active).

## Le projet
Le virus est un programme appelé MediaPlayer.exe.  
Il cible tous les fichiers exécutables du répertoire courant. Pour chaque cible, il la renomme en lui accolant l'extension ".old", et le virus en cours d'exécution se recopie lui même et prend le nom du programme ciblé.  
Le virus contient lui même des instructions qui permettent le transfert d'exécution au programme appelé par l'utilisateur de manière à éviter les soupçons.
![principeVirus](https://i.imgur.com/oYFZa0a.jpg)
