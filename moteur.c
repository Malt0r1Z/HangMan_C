#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "moteur.h"
#include "readFile.h"
#include "liste.h"

#define ERREUR_MAXIMUM  6

/*
*Initialise une nouvelle partie du jeu
Elle charge un dictionnaire et,tire un mot aléatoirement et initialise les variables de la partie
* Antécédent : le dictionnaire doit exister et contenir des mots valides
*/

Partie *init_Partie(char *dictionnaire) {
    Partie *p = malloc(sizeof(Partie));
    if (!p) return NULL;
    Liste dico = getDico(dictionnaire);
    char *mot = randomMot(dico);  // mot aléatoire depuis le dictionnaire

    //mot est tiré au hasard du dictionnaire 
    if(!mot) {
        free(p);
        return NULL;
    }
    int longeur_mot= strlen(mot);
    //longeur_mot est la longueur du mot tiré
    p->mot_cherche=malloc(longeur_mot+1);//allocation dynamique 
    strcpy(p->mot_cherche, mot);
    //allocation dynamique du mot à trouver 
    p->mot_affiche = malloc(longeur_mot + 1);
    for(int i=1;i<=longeur_mot ;i++) p->mot_affiche[i-1] = 'x';//caracteres x pour masquer le mot a trouver 
    p->mot_affiche[longeur_mot] = '\0'; 
    for (int i = 0; i < 26; i++) {
        //tableau des lettres deja utilisées intialisé à zéro, car début du jeu  
        p->alphabet[i] = 0;
    }

    p->nb_erreurs = 0;
    //le nombre d'erreurs est initialisé à zéro 
    p->nblettres_trouve = 0;
    //le nombre de lettres trouvées est initialisé à zéro
    return p;
    //pointeur vers la partie initialisée 
}

/*
 Rôle :Initialise une partie en utilisant le dictionnaire francais 
 */
Partie* init_Partie_fr(void) {
    return init_Partie("dico_fr.txt");
}
/*
 Rôle :Initialise une partie en utilisant le dictionnaire anglais
 */
Partie* init_Partie_ang(void) {
    return init_Partie("dico_uk.txt");
}


/*
 Rôle :Vérifie si la partie est finie, soit si le mot est trouvé soit si le nombre maximum d'erreurs est atteint
 */
void fin_partie(Partie *p) {
    if (p->nblettres_trouve == strlen(p->mot_cherche)) {
        // Le mot a été trouvé
            printf("Gagné! Le mot etait bien:  %s\n", p->mot_cherche);

    } else if (p->nb_erreurs >= ERREUR_MAXIMUM) {
        // Le nombre maximum d'erreurs est atteint
        printf("Perdu ! Le mot était: %s\n", p->mot_cherche);
    }
}


/*
 Rôle :Libère la mémoire allouée pour la partie et affiche un message de fin
 */
void quitter_partie(Partie *p) {
    // Libération de la mémoire utilisée pour la partie
    if (p) {
        free(p->mot_affiche);
        free(p->mot_cherche);
        free(p);
    }
    printf("Vous avez quitté la partie :( \n");
}

/*
 Rôle :Affiche les lettres déjà proposées par le joueur
 */
 void lettre_utilisee(Partie *p){
    printf("Lettres proposées : ");
    for (int i=0;i<26;i++) {
        if (p->alphabet[i]) {
            printf("%c ", 'a' + i);
        }
    }
    printf("\n");
 }



 /*
*Role :Renvoie vrai si la partie est terminée, faux sinon
* Antécédent : la partie doit être initialisée
*/
int terminee(Partie *p) {
    //La partie est terminée si le mot a été trouvé ou si le nombre d'erreurs= ERREUR_MAXIMUM 
    return gagnee(p)||(p->nb_erreurs >= ERREUR_MAXIMUM);
}

/*
*Role :Renvoie vraie si le mot a été trouvé, faux sinon
* Antécédent : la partie doit être initialisée
*/
int gagnee(Partie *p) {
    return strcmp(p->mot_cherche,p->mot_affiche) == 0;
}


/*
 * Rôle : Affiche le mota trouver en remplacant les lettresnon trouvées par des 'x'
 *       Antécédent : la partie doit être initialisée
 */
void mot_en_cours(const Partie *p) {
    printf("Mot à trouver:");
    for (int i=0;p->mot_affiche[i]!='\0'; i++) {
        printf("%c",p->mot_affiche[i]);
    }
    printf("\n");
}
/*
*Role : Verifie si la lettre choisie est valide ou pas en l'ajoutant si oui au tableau des lettres deja utilisés
*/
int validite_lettre(Partie *p,char choix) {
   // choix = tolower(choix); on convertis en minuscule pour pouvoir gerer les lettres saisies
   //La lettre est convertie en minuscule 
   
    if (choix<'a'||choix>'z') {
        return 0;
         //Si la lettre n'est pas dans l'alphabet =>lettre invalide
    }
   //La lettre est dans l'alphabet
    int index = choix-'a';
    //On vérifie si la lettre à deja ete proposée
    if (p->alphabet[index]){
        return 0; 
        //La lettre a deja été proposée
    } 
    //la lettre n'a pas été proposée
    p->alphabet[index] = 1; 
    //On met la lettre dans le tableau des lettres utilisées
    int valide=0;
    for (int i=0;p->mot_cherche[i] != '\0'; i++) {
        if (p->mot_cherche[i]==choix) {
            p->mot_affiche[i]=choix;
            //On remplace le 'x' par la lettre valide
            //On incrémente le nombre de lettres trouvées
            p->nblettres_trouve++;
            valide=1;
        }
    }
    //La lettre n'est pas presente dans le mot
    if (!valide) p->nb_erreurs++;
    //Le nombre d'erreurs est incrémenté
    return valide;
}
/*
