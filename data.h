/*
 * data.h
 *
 *  Ndeye khady DIOP & Alex MEURILLON ELSE3
*/

#pragma once

typedef struct {
    char *mot_cherche;
    char *mot_affiche;
    char alphabet[26];
    int nb_erreurs;
    int nblettres_trouve;
} Partie;

extern Partie *init_Partie(char *);
extern Partie *init_Partie_ang(void);
extern Partie *init_Partie_fr(void);
int erreurs(const Partie *);

extern void lettre_utilisee(const Partie *,    char *);
extern void quitter_partie(Partie *);
extern int validite_lettre(Partie * , char );
extern int terminee(Partie *);
extern int gagnee(Partie *);
extern const char *mot_en_cours(const Partie *);


//GESTION DES ERREURS
extern void setErreur_max(int );
extern int get_erreur_max(void);
extern void setErreur(char *);

extern const char *get_mot_cherche(const Partie *);
