//
// data.c
// 
// Ndeye Khady DIOP & Alex MEURILLON ELSE3
//
// Ce fichier implémente la gestion des données  du jeu de pendu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "data.h"
#include "readFile.h"
#include "liste.h"

int ERREUR_MAXIMUM = 8; // costante maximum d'erreurs autorisées. Par défaut, 8 erreurs sont autorisées.

/*
 * Rôle : Initialise une nouvelle partie en utilisant le dictionnaire spécifié en paramètres 
 *         et renvoie un pointeur vers la structure Partie initialisée
 *        Antécédent : le dictionnaire doit exister et contenir des mots valides
*/
Partie *init_Partie(char *dictionnaire) {
    printf("J'init_Partie\n");
    Partie *p = malloc(sizeof(Partie));
    if (!p) return NULL;
    //Récuperation du mot et sélection d'un mot aléatoire
    Liste dico = getDico(dictionnaire);
    char *mot = randomMot(dico); 
    //mot est tiré au hasard du dictionnaire 

    if(!mot) {
        //Aucun mot n'a été selectionné
        free(p);
        return NULL;
    }
    //Un mot est bien selectionné dans le dictionnaire 
    int longueur_mot= strlen(mot);
    //longueur_mot est la longueur du mot tiré


    //Allocation dynamique et initialisation  du mot à trouver par l'utilisateur 
    p->mot_cherche=malloc(longueur_mot+1);
    strcpy(p->mot_cherche, mot);
    p->mot_affiche = malloc(longueur_mot + 1);

        
    // Initialisation du mot affiché avec des '_'
    for(int i=1;i<=longueur_mot ;i++) p->mot_affiche[i-1] = '_';
    p->mot_affiche[longueur_mot] = '\0'; 
    for (int i = 0; i < 26; i++) {
    //le tableau des lettres deja utilisées intialisé à zéro, car début du jeu  
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
 * Rôle :Initialise une partie en utilisant le dictionnaire français et renvoie 
 *       un pointeur vers la partie initialisée
 */
Partie* init_Partie_fr(void) {
    return init_Partie("dico_fr.txt");
}

/*
 * Rôle :Initialise une partie en utilisant le dictionnaire anglais et renvoie 
 *       un pointeur vers la partie initialisée
 */
Partie* init_Partie_ang(void) {
    return init_Partie("dico_uk.txt");
}

/*
 Rôle : Renvoie le nombre d'erreurs commises par le joueur
 Antécédent : la partie doit être initialisée
 */
int erreurs(const Partie *p) {
    return p->nb_erreurs;
}

/*
 * Rôle : Libère la mémoire allouée pour la partie p 
 */
void quitter_partie(Partie *p) {
    // Libération de la mémoire utilisée pour la partie
    if (p) {
        //la partie p est initialisée
        if (p->mot_cherche) free(p->mot_cherche);
        if (p->mot_affiche) free(p->mot_affiche);
        free(p);
    }
}

/*
 * Rôle : Affiche les lettres déjà proposées par le joueur
 * Antécédent : la partie doit être initialisée
*/
void lettre_utilisee(const Partie *p, char *lettres_impossibles){
    int k=0;
    for (int i=0;i<26;i++) {
        
        if (p->alphabet[i]) {
            lettres_impossibles[k++]= 'a' + i;
            //lettres_impossibles contient les lettres déjà essayées
            //On ajoute la lettre dans le tableau des lettres utilisées
        }
    }
    lettres_impossibles[k] = '\0'; // Terminer la chaîne de caractères par le caractère de fin.
}

/*
 * Rôle : Teste si la partie est terminée et renvoie 1 si 
 *       la partie est terminée(victoire ou défaite) ), 0 sinon
 * Antécédent : la partie doit être initialisée
*/
int terminee(Partie *p) {
    // La partie est terminée si le mot a été trouvé ou si le nombre d'erreurs= ERREUR_MAXIMUM 
    return gagnee(p)||(p->nb_erreurs >= get_erreur_max());
}

/*
 * Rôle : Teste si le joueur a gagné la partie retourne  1 si le mot a été trouvé, 0 sinon
 * Antécédent : la partie doit être initialisée
*/
int gagnee(Partie *p) {
    //le mot est trouvé si mot_affiche == mot_cherche
    return strcmp(p->mot_cherche,p->mot_affiche) == 0;
}

/*
 * Rôle : Renvoie  l'état actuel du mot à deviner  mot_affiche (chaîne de '_' et lettres trouvées)
 * Antécédent : la partie doit être initialisée
 */
const char *mot_en_cours(const Partie *p) {
    return p->mot_affiche;
}

/*
 * Rôle : renvoie le mot à deviner
 * Antécédent : la partie doit être initialisée
*/
const char *get_mot_cherche(const Partie *p) {
    return p->mot_cherche;
}

/*
 * Rôle : Verifie si la lettre choisie est valide ou pas en l'ajoutant si oui au tableau des lettres deja utilisés
 *        Renvoie :
 *        0 => la lettre est  invalide ou déjà proposée
 *        1 => lettre correcte et potentiellement victoire 
 *        2 => lettre incorrecte et potentiellement défaite
 * Antécédent : la partie doit être initialisée
 *        
*/
int validite_lettre(Partie *p,char choix) {
   choix = tolower(choix); //conversion en minuscule 

    if (!isalpha(choix)) {
        return 0; //   //Si la lettre n'est pas dans l'alphabet =>lettre invalide 
    }
   //La lettre est dans l'alphabet
    int indice = choix-'a';
    //On vérifie si la lettre à déja été proposée
    if (p->alphabet[indice]){
        return 0; 
        //La lettre a deja été proposée
    } 
    //la lettre n'a pas été proposée
    p->alphabet[indice] = 1; 
    //On met la lettre dans le tableau des lettres utilisées
    int valide=0;
    for (int i=0;p->mot_cherche[i] != '\0'; i++) {
        if (p->mot_cherche[i]==choix) {
            p->mot_affiche[i]=choix;
            //On remplace le '_' par la lettre valide
            //On incrémente le nombre de lettres trouvées
            p->nblettres_trouve++;
            valide=1;
        }
    }
    //La lettre n'est pas présente dans le mot
      if (!valide) {
        p->nb_erreurs++;// incrementer le nombre d'erreur 
        if (p->nb_erreurs >= get_erreur_max()) {//verifier si apres incrémentation on atteint pas la limite
            valide= 2; // Perdu
        }
  }
    // Vérifier si le mot est complet
    if (gagnee(p)) {
        valide =1; // 1 si gagné
    }
    return valide;

}

/*
 * Rôle : Définit le nombre maximum d'erreurs autorisées
 *  Antécédent : valeur doit être un entier positif 6<=valeur<=8
*/
void setErreur_max(int valeur) {
    ERREUR_MAXIMUM = valeur;
}


/*
 * Rôle : Renvoie le nombre maximum d'erreurs autorisées
*/
int get_erreur_max(void) {
    return ERREUR_MAXIMUM;
}

/*
 * Rôle : Définit le nombre maximum d'erreurs en fonction de la difficulté choisie
 *        Antécédent : difficulte doit être une chaîne de caractères valide
 */
void setErreur(char *difficulte) {
    if (strcmp(difficulte, "Facile") == 0) {
        setErreur_max(8);
        //niveau facile => erreur maximum fixé à 8
    } else if (strcmp(difficulte, "Moyen") == 0) {
        setErreur_max(7);
        //niveau moyen => erreur maximum fixé à 7
    } else if (strcmp(difficulte, "Difficile") == 0) {
        setErreur_max(6);
        //niveau difficile => erreur maximum fixé à 6
    } else {
        //difficulté inconnue, message d'erreur 
        fprintf(stderr, "Difficulté inconnue : %s\n", difficulte);
    }
}