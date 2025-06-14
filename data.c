#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "data.h"
#include "readFile.h"
#include "liste.h"


int ERREUR_MAXIMUM = 8; // Nombre maximum d'erreurs autorisées. Par défaut, 8 erreurs sont autorisées.



/*
 * Rôle : Initialise une partie en utilisant le dictionnaire spécifié
 *        Antécédent : le dictionnaire doit exister et contenir des mots valides
*/
Partie *init_Partie(char *dictionnaire) {
    printf("J'init_Partie\n");
    Partie *p = malloc(sizeof(Partie));
    if (!p) return NULL;
    Liste dico = getDico(dictionnaire);
    char *mot = randomMot(dico);  // mot aléatoire depuis le dictionnaire
    printf("Le mot choisi est : %s\n", mot); // DEBUG
    //mot est tiré au hasard du dictionnaire 
    if(!mot) {
        free(p);
        return NULL;
    }
    int longueur_mot= strlen(mot);
    //longueur_mot est la longueur du mot tiré
    p->mot_cherche=malloc(longueur_mot+1);//allocation dynamique 
    strcpy(p->mot_cherche, mot);
    //allocation dynamique du mot à trouver 
    p->mot_affiche = malloc(longueur_mot + 1);
    for(int i=1;i<=longueur_mot ;i++) p->mot_affiche[i-1] = '_';//caracteres _ pour masquer le mot a trouver 
    p->mot_affiche[longueur_mot] = '\0'; 
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
 Rôle : Renvoie le nombre d'erreurs commises par le joueur
 Antécédent : la partie doit être initialisée
 */
int erreurs(const Partie *p) {
    return p->nb_erreurs;
}

/*
int fin_partie(Partie *p) {
    if (!p || !p->mot_cherche) {
        fprintf(stderr, "Erreur: partie ou mot_cherche NULL dans fin_partie\n");
        return -1;
    }
    if (p->nblettres_trouve == strlen(p->mot_cherche)) {
        return 0;
    } else if (p->nb_erreurs >= get_erreur_max()) {
        return 1;
    }
    return -1;
}
*/

/*
 Rôle :Vérifie si la partie est finie, soit si le mot est trouvé (renvoie 0)soit si le nombre maximum d'erreurs est atteint(renvoie 1)

int fin_partie(Partie *p) {
    printf("Je suis dans fin_partie\n");
    printf("Le nombre de lettres trouvées est : %d\n", p->nblettres_trouve);
    printf("La longueur du mot cherché est : %ld\n", strlen(p->mot_cherche));
    
    if (p->nblettres_trouve == strlen(p->mot_cherche)) {
        // Le mot a été trouvé
        return 0 ;
    } else if (p->nb_erreurs >= get_erreur_max()) {
        // Le nombre maximum d'erreurs est atteint
       return 1;
    }
    //La partie est toujours en cours 
    return -1;
}
*/




/*
 * Rôle : Libère la mémoire allouée pour la partie
 */
void quitter_partie(Partie *p) {
    // Libération de la mémoire utilisée pour la partie
    if (p) {
        if (p->mot_cherche) free(p->mot_cherche);
        if (p->mot_affiche) free(p->mot_affiche);
        free(p);
        p = NULL; // Mettre le pointeur à NULL pour éviter les accès ultérieurs
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
            //On ajoute la lettre dans le tableau des lettres utilisées
        }
    }
    lettres_impossibles[k] = '\0'; // Terminer la chaîne de caractères
}




/*
 * Rôle : Renvoie vrai si la partie est terminée, faux sinon
 * Antécédent : la partie doit être initialisée
*/
int terminee(Partie *p) {
    // La partie est terminée si le mot a été trouvé ou si le nombre d'erreurs= ERREUR_MAXIMUM 
    return gagnee(p)||(p->nb_erreurs >= get_erreur_max());
}





/*
 * Rôle : Renvoie vraie si le mot a été trouvé, faux sinon
 * Antécédent : la partie doit être initialisée
*/
int gagnee(Partie *p) {
    return strcmp(p->mot_cherche,p->mot_affiche) == 0;
}




/*
 * Rôle : Affiche le mota trouver en remplacant les lettresnon trouvées par des 'x'
 * Antécédent : la partie doit être initialisée
 */
const char *mot_en_cours(const Partie *p) {
     //printf("Affichage en cours : %s\n", p->mot_affiche); // DEBUG
    return p->mot_affiche;
}





/*
 * Rôle : Verifie si la lettre choisie est valide ou pas en l'ajoutant si oui au tableau des lettres deja utilisés
 * Antécédent : la partie doit être initialisée
 *            : la lettre choisie doit être une lettre de l'alphabet
*/
int validite_lettre(Partie *p,char choix) {
   choix = tolower(choix); //on convertis en minuscule pour pouvoir gerer les lettres saisies
   //La lettre est convertie en minuscule 
   
    if (!isalpha(choix)) {
        return 0; //   //Si la lettre n'est pas dans l'alphabet =>lettre invalide 
    }
   //La lettre est dans l'alphabet
    int indice = choix-'a';
    //On vérifie si la lettre à deja ete proposée
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
    //La lettre n'est pas presente dans le mot
    //On sépare car terminee() prends en compte gagner et perdre 
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

// Gestion des erreurs


/*
 * Rôle : Définit le nombre maximum d'erreurs autorisées
    * Antécédent : valeur doit être un entier positif 6<=valeur<=8
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
    } else if (strcmp(difficulte, "Moyen") == 0) {
        setErreur_max(7);
    } else if (strcmp(difficulte, "Difficile") == 0) {
        setErreur_max(6);
    } else {
        fprintf(stderr, "Difficulté inconnue : %s\n", difficulte);
    }
}

/*
 * Rôle : renvoie le mot à trouver
 * Antécédent : la partie doit être initialisée
*/
const char *get_mot_cherche(const Partie *p) {
    return p->mot_cherche;
}