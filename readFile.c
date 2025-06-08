//
// readFile.c
//
// Khady Ndaye DIOP & Alex MEURILLON ELSE3

// Ce fichier permet de lire le dictionnaire, sélectionner les mots désirés et trouver le mot pour le jeu
// de pendu

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "readFile.h"
#include "liste.h"




/*
 Antécédent : les mots contenus dans le fichier sont écrits une seule et unique fois
 Rôle : Génère et renvoie notre dictionnaire
 */
Liste getDico(const char *f){
    FILE *fd;
    // Ouvrir le fichier 'f' en lecture
    // Gestion d'erreur d'un fichier vide
    if ((fd = fopen(f, "r")) == NULL){
        perror(f);
        exit(errno);
    }
    
    // Fichier non-vide
    Liste l = initListe();
    
    // On parcourt l'entiereté du fichier en sélectionnant les mots de 6 à 8 caractères
    // A FAIRE : tous miniscules ou majuscules ? est-ce que ca gene vraiement ? juste faire un tolower()...
    char buf[BUFSIZ]; // buf est un pointeur
    while(fgets(buf, sizeof(buf), fd) != NULL){
        // On remplace le saut de ligne par le carctère de fin de chaîne
        buf[strcspn(buf, "\n")] = 0;
        int len = strlen(buf);
        if (len >= 6 && len <= 8) {
            // Duplication du mot pour l’ajouter à la liste
            char *mot = strdup(buf);
            inserer(&l, 1, mot);
        }
    }
    
    // Fermer le fichier
    if (fclose(fd)==EOF){
        perror(f);
        exit(errno);
    }
    // Renvoyer notre dictionnaire de jeu
    return l;
}


/*
 Rôle : Renvoie, de manière pseudo-aléatoire, un mot parmi la liste l passée en paramètre
 */
char* randomMot(const Liste l){
    // Génération du germe pour trouver une valeur pseudo-aléatoire
    srandom(time(NULL));
    // On cherche un nombre aléatoire entre 1 et la longueur de la liste
    // On l'écrit : random() % (max + 1 - min) + min
    int longueurDico = longueur(l);
    int positionMot = random() % (longueurDico + 1 - 1 ) + 1;
    // On renvoie le mot sélectionné
    return ieme(l,positionMot);
}

/*int main(void){
    // Exemple d'utilisation de getDico et randomMot
    Liste dico = getDico("dico_fr.txt");
    
    char *mot = randomMot(dico);
    printf("Mot aléatoire choisi : %s\n", mot); 
    return EXIT_SUCCESS;
}*/
