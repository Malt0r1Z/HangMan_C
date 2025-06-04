#pragma once 


typedef struct {
    char *mot_cherche;
    char *mot_affiche;
    char alphabet[26];
    int nb_erreurs;
    int nblettres_trouve;
} Partie;
extern Partie *init_Partie (char *dictionnaire);
extern Partie *init_Partie_ang(void);
extern Partie *init_Partie_fr(void);
extern void lettre_utilisee(Partie *p);
extern void fin_partie(Partie *p);
extern void quitter_partie(Partie *p);
extern int validite_lettre(Partie *p, char choix);
extern void statut_joueur(const Partie *p);
extern int terminee(Partie *p);
extern int gagnee(Partie *p);
extern void mot_en_cours(const Partie *p);

