/*
 * callbacks.c
 *
 * Ndeye khady DIOP & Alex MEURILLON ELSE3
*/

#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include "callbacks.h"
#include "data.h"


Partie *jeu=NULL; // Pointeur vers la partie en cours

char *choix_langue = "Français"; // Pointeur pour stocker le choix de langue,francais par defaut 


static Widget descriptif;

static Widget erreurs_maximum; //pour configurer le nombre max d'erreurs

/*
   Rôle : Ferme la fenêtre ouverte
*/
static void annuler(Widget w, void *d){
  CloseWindow();
}
/*
  Rôle : Choix du dictionnaire français
  Affiche un message de confirmation et relance le jeu avec la langue sélectionnée
*/
static void setLangue_fr(Widget w, void *d){
    choix_langue = "Français";
    ShowMessage("Dictionnaire sélectionnée:Français");
    rejouer(NULL, NULL);
  // Logique pour changer la langue en français
  CloseWindow();
}


/*
  Rôle : Choix du dictionnaire anglais
  Affiche un message de confirmation et relance le jeu avec la langue sélectionnée
*/
static void setLangue_uk(Widget w, void *d){
  choix_langue = "Anglais";
  ShowMessage("dictionary selected:English ");
  rejouer(NULL, NULL);
  // Logique pour changer la langue en anglais
  CloseWindow();
}



/*
 * Rôle : Recupère la valeur entrée par l'utilisateur pour le nombre maximum d'erreurs
*/
void appliquer_erreur_max(Widget w, void *d) {
    const char *valeur = GetStringEntry(erreurs_maximum);
    int erreur_entree= atoi(valeur);
    if (erreur_entree >=1&& erreur_entree<= 6) {
        setErreur_max(erreur_entree);
        ShowMessage("Nombre d'erreurs maximum appliqué");
    } else {
        ShowMessage("L'erreur maximum doit être un nombre entre 1 et 6");
    }
    CloseWindow();
}



/*
 * Rôle :Affichage d'une fenêtre pour configurer le nombre maximum d'erreurs
*/
void erreur(Widget w, void *d) {
    // Logique pour configurer le nombre d'erreurs maximum :
    MakeWindow("Configurer l'erreur maximum",SAME_DISPLAY,EXCLUSIVE_WINDOW);
    MakeLabel("Entrez le nombre d'erreurs maximum");
    erreurs_maximum =MakeStringEntry(NULL,1,NULL,d);
    Widget BAppliquer =MakeButton("Valider",appliquer_erreur_max, NULL);
    Widget BAnnuler =MakeButton("Annuler",annuler, NULL);
    SetWidgetPos(BAppliquer,PLACE_RIGHT,BAnnuler, PLACE_UNDER, erreurs_maximum);
    SetWidgetPos(BAnnuler,PLACE_UNDER,erreurs_maximum, NO_CARE, NULL);
    ShowDisplay();
}


/*
Rôle : Initialiser le jeu en fonction du dictionnaire choisi
*/
void initGame() {
    if (strcmp(choix_langue,"Français") == 0)
        jeu=init_Partie_fr();
    else
        jeu=init_Partie_ang();
}


/*
 * Rôle : Lance une nouvelle partie du jeu
*/

void rejouer(Widget w, void *d){
    printf("Rejouer button cliqué\n");
    //J'ai ajouté cette ligne, car il faut libérer la mémoire de la partie précédente avant d'en initialiser une nouvelle
    quitter_partie(jeu); // Libère la mémoire de la partie précédente
    initGame(); 

    CloseWindow();
}
/*
  Rôle :Menu, affiche une fenetre avec les options
 
*/
void menu(Widget w, void *d){
    printf("Menu button cliqué\n");
    // Logique pour afficher le menu :
    MakeWindow("Langues préférées", SAME_DISPLAY, EXCLUSIVE_WINDOW);
   
    descriptif = MakeLabel("Sélectionnez votre langue préférée :");
    SetWidgetPos(descriptif, PLACE_ABOVE, w, NO_CARE, NULL);
   
    Widget BLangue_fr = MakeButton("Français", setLangue_fr, NULL);
    Widget BLangue_uk = MakeButton("Anglais", setLangue_uk, d);
    Widget BAnnuler = MakeButton("Annuler", annuler, NULL);
    // Widget BErreurs= MakeButton("Configurer l'erreur  maximum ", erreur, NULL);

    SetWidgetPos(BLangue_fr, PLACE_UNDER, entree, NO_CARE, NULL);
    SetWidgetPos(BLangue_uk, PLACE_RIGHT, BLangue_fr, PLACE_UNDER, entree);
    SetWidgetPos(BAnnuler, PLACE_UNDER, BLangue_fr, NO_CARE, NULL);

   // SetWidgetPos(BErreurs, PLACE_UNDER, BAnnuler, NO_CARE, NULL);

    ShowDisplay();
    MainLoop();
}



/*
 * Menu "Aide" pour afficher les règles du jeu
*/

static Widget explication;

void aide(Widget w, void *d){
    printf("Aide button cliqué\n");
    // Logique pour afficher l'aide :
    MakeWindow("Aide", SAME_DISPLAY, EXCLUSIVE_WINDOW);
    explication = MakeTextWidget("aide.txt", 0, 0, 300, 200);
    Widget BOK = MakeButton("OK", annuler, NULL);
    SetWidgetPos(explication, PLACE_ABOVE, BOK, NO_CARE, NULL);
    SetWidgetPos(BOK, PLACE_UNDER, explication, NO_CARE, NULL);
    ShowDisplay();
    MainLoop();
}