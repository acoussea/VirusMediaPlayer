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

## Développement
### Choix d'implémentation
De nombreux points du développement requièrent des choix et pourraient être implémentés de façons différentes. Ici, nous répertorions les principaux choix effectués lors de la conception du virus :
- **Servir l’utilisateur :** Afin de ne pas éveiller les soupçons le MediaPlayer doit, en plus de propager le virus, afficher une image du dossier.
    -  Pour cela, nous avons premièrement choisi d’implémenter une fonction d’affichage avec GTK permettant d’afficher une image du dossier, de naviguer parmis les autres images du dossier. Il permet également de choisir manuellement une image à afficher dans le dossier.
    - Après réflexion, nous avons également fait une deuxième version de la fonction d’affichage, qui appelle seulement grâce à la fonction C “system” le MediaPlayer de base de Linux. Cette version permet premièrement d’être plus fidèle visuellement à un MediaPlayer , mais également de réduire les dépendances car ne nécessite pas l’installation de GTK, et se faisant, d’augmenter les chances d’infection.  
- **Lutter contre la surinfection :** Plus l’infection est importante, plus l’utilisateur aura de chances de s’en rendre compte et de supprimer toute menace. Afin de permettre au virus de rester le plus discret possible et ne pas être détecté, nous avons choisi d’infecter un nombre fixe de programmes, ainsi seulement 3 programmes seront la cible du virus à chaque exécution ou moins si le
nombre de programmes est insuffisant.  
- **Nuisance du Virus :** Tout programme autoréplicatif et autopropageable est un virus, il n’est donc pas nécessairement malveillant et ne produit donc pas toujours de nuisance. Afin de simplifier les tests et le développement du virus, nous avons donc décidé de ne pas inclure de nuisance autre que.  
- **Copie du Virus :** Afin de permettre l’infection et la propagation du Virus, celui ci doit se recopier et se faire passer pour les programmes cibles. Plusieurs possibilités de copies s’offraient à nous. Par exemple un simple l’appel direct au virus initial (MediaPlayer.exe) au lieu d’une réelle copie, ou une copie renommée de l'exécutable MediaPlayer.exe. Nous avons donc choisi de copier non pas le MediaPlayer, mais le programme infecté exécuté. Ainsi, si un programme infecté est déplacé puis exécuté, il fonctionnera même sans la présence du virus initial.

### Fonctions principales

- **searchFiles :** Cette fonction permet de rechercher dans le fichier courant tous les fichiers qui sont exécutables et donc sujet à être infectés. Une liste de 3 fichiers est ainsi renvoyée pour passer à l’étape d’infection.
- **dejaInfecte :** Cette fonction s’occupe d’effectuer la double vérification sur chaque fichier pendant l’étape de recherche. Elle renvoie un booléen pour savoir si le fichier est déjà infecté ou non, en vérifiant son extension, puis en vérifiant si le répertoire courant contient cet exécutable en version “.old”.
- **infecte :** Pour chacun des fichiers sélectionnés, cette fonction s’occupe de créer une copie du fichier virus appelé, et renomme le fichier ciblé avec l’extension “.old”.
- **execution :** Cette fonction s’occupe de l’exécution du programme pour “rendre service” à l’utilisateur. Si le virus lancé est le MediaPlayer, il affiche une image, sinon il fait un appel au fichier “.old” correspondant au virus appelé.

### Offuscation de code
Afin de rendre le code illisible pour l’homme et de maximiser les chances de survie du virus dans l’éventualité où l'utilisateur utiliserait un désassembleur pour lire le code source, plusieurs méthodes d’obfuscation de code ont été utilisées.
1) Chaque fonctions et variables du code sources ont été renommées afin d’être cohérentes avec des noms de fonctions d’un programme de MediaPlayer. Ainsi la fonction de recherche de fichier s’appelle “RechercheImage”, celle d’infection a été renommée “LoadImage”, et celle qui vérifie l’infection “dejaInfecte” a été renommée “isImageDispo”.
2) Du code mort a été ajouté à quelques endroits en initialisant des tableaux et variables non utilisées dans la suite du code, afin de brouiller les pistes.
3) Afin de réduire les chances de compréhension, du code “rare” a été ajouté par endroit, comme par exemple des opérateurs ternaires à la place de “if”, ou la suppression d’accolades pour que l’utilisateur ne soit pas certain du début et de la fin de certains blocs.
4) Pour finir, la suppression d’indentation et d’espaces dans le code permet de rendre suffisamment illisible le code pour l’humain.
