Bienvenue dans le jeu du Pendu !
Pour lancer une partie, rendez-vous dans le dossier HangMan_C de l'archive décompressée de ce projet.
Exécutez les commandes suivantes :
$ make
$ ./hangman

Si le message d'erreur suivant apparaît dans le terminal, ne vous inquétez pas, cela se
produit lorsque l'interface graphique possède plusieurs Widgets ce qui est forcément notre cas !
'Warning : Reprensation size 8 must match superclass's to override visual'

Si c'est le cas, privilégié ces 2 commandes qui permettent de rediriger la sortie standard d'erreur :
$ make
$ ./hangman 2>/dev/null

Enjoy !