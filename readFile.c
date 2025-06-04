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
    /*
    char caractereCourant;
    while (fread(&caractereCourant, sizeof(char), 1, fd) > 0){
        // Vérification de la taille et de la diacritique du mot
        int tailleMot = strlen(caractereCourant)
        if (tailleMot>=6 && tailleMot<=8 && isalpha()!=0){
            // Taille valide, on l'ajoute à notre Dictionnaire, en sommet.
            char *motAAjouter = malloc(sizeof(char));
            inserer(l, 1, motAAjouter);
        }
    }
    */
    char buf[BUFSIZ]; // buf est un pointeur
    int lg;
    // Vérifier si le fichier est vide ou s'il y a une erreur avec que ça renvoie NULL
    while(fgets(buf,sizeof(buf),fd) != NULL){
        // On vérifie que le mot n'est pas vide (Ligne vide)
        if (strlen(buf) > 0) {
            // On enlève le saut de ligne à la fin du mot
            // buf[strcspn(buf, "\n")] = 0;
            // On ajoute le mot à notre liste
            inserer(l, 1, buf);
        }
    }
    
    // Fermer les fichiers
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
char* randomMot(const Liste *l){
    // Génération du germe pour trouver une valeur pseudo-aléatoire
    srandom(time(NULL));
    // On cherche un nombre aléatoire entre 1 et la longueur de la liste
    // On l'écrit : random() % (max + 1 - min) + min
    int longueurDico = longueur(&l);
    int positionMot = random() % (longueurDico + 1 - 1 ) + 1;
    // On renvoie le mot sélectionné
    return ieme(&l,positionMot);
}

int main(void){
    // Exemple d'utilisation de getDico et randomMot
    Liste dico = getDico("dictionnaire.txt");
    char *mot = randomMot(&dico);
    printf("Mot aléatoire choisi : %s\n", mot); 
    return EXIT_SUCCESS;
}