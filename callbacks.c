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

char *choix_langue = "francais"; // Pointeur pour stocker le choix de langue,francais par defaut 


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
    choix_langue = "francais";
    GetOkay("Dictionnaire selectionnee : francais");
    //ShowMessage("Dictionnaire sélectionnée:français");
    rejouer(NULL, NULL);
  // Logique pour changer la langue en français
  //CloseWindow();
}


/*
  Rôle : Choix du dictionnaire anglais
  Affiche un message de confirmation et relance le jeu avec la langue sélectionnée
*/
static void setLangue_uk(Widget w, void *d){
  choix_langue = "Anglais";
  GetOkay("Dictionnaire selectionnee : anglais");
  //ShowMessage("dictionary selected:English ");
  rejouer(NULL, NULL);
  // Logique pour changer la langue en anglais
  //CloseWindow();
}



/*
 * Rôle : Recupère la valeur entrée par l'utilisateur pour le nombre maximum d'erreurs
*/
void appliquer_erreur_max(Widget w, void *d) {
    const char *valeur = GetStringEntry(erreurs_maximum);
    int erreur_entree= atoi(valeur);
    if (erreur_entree >=1&& erreur_entree<= 6) {
        setErreur_max(erreur_entree);
        GetOkay("Nombre d'erreurs maximum applique");
        //ShowMessage("Nombre d'erreurs maximum appliqué");
    } else {
        GetOkay("L'erreur maximum doit etre un nombre entre 1 et 6");
        // ShowMessage("L'erreur maximum doit être un nombre entre 1 et 6");
    }
    //CloseWindow();
}

/*
 * Rôle : Affiche à l'écran une fenêtre pour choisir le niveau de difficulté
*/
void choix_difficulte(Widget w, void *d) {
    char *difficulte = NULL;

    // Callback interne pour chaque bouton
    void bouton_cb(Widget w, void *d) {
        difficulte = (char*)d;
        CloseWindow();
        printf("Difficulté choisie : %s\n", difficulte);
    }

    MakeWindow("Choix de la difficulté", SAME_DISPLAY, EXCLUSIVE_WINDOW);
    Widget bFacile = MakeButton("Facile", bouton_cb, "Facile");
    Widget bMoyen = MakeButton("Moyen", bouton_cb, "Moyen");
    Widget bDifficile = MakeButton("Difficile", bouton_cb, "Difficile");

    SetWidgetPos(bFacile, NO_CARE, NULL, NO_CARE, NULL);
    SetWidgetPos(bMoyen, PLACE_RIGHT, bFacile, NO_CARE, NULL);
    SetWidgetPos(bDifficile, PLACE_RIGHT, bMoyen, NO_CARE, NULL);

    ShowDisplay();
    MainLoop();

}


/*
Rôle : Initialiser le jeu en fonction du dictionnaire choisi
*/
void initGame() {
    if (strcmp(choix_langue,"francais") == 0) {
        jeu=init_Partie_fr();
    }
    else {
        printf("Initialisation du jeu en anglais\n");
    }
}


/*
 * Rôle : Lance une nouvelle partie du jeu
*/

void rejouer(Widget w, void *d){
    //J'ai ajouté cette ligne, car il faut libérer la mémoire de la partie précédente avant d'en initialiser une nouvelle
    quitter_partie(jeu); // Libère la mémoire de la partie précédente
    initGame(); 

    CloseWindow();
}
/*
  Rôle :Menu, affiche une fenetre avec les options
 
*/
void menu(Widget w, void *d){
    // Logique pour afficher le menu :
    MakeWindow("Langues préférées", SAME_DISPLAY, EXCLUSIVE_WINDOW);
   
    descriptif = MakeLabel("Selectionnez votre langue preferee :");
    SetWidgetPos(descriptif, PLACE_UNDER, w, NO_CARE, NULL);
   
    Widget BLangue_fr = MakeButton("Francais", setLangue_fr, NULL);
    Widget BLangue_uk = MakeButton("Anglais", setLangue_uk, d);
    Widget BAnnuler = MakeButton("Annuler", annuler, NULL);
    // Widget BErreurs= MakeButton("Configurer l'erreur  maximum ", erreur, NULL);

    SetWidgetPos(BLangue_fr, PLACE_UNDER, descriptif, NO_CARE, NULL);
    SetWidgetPos(BLangue_uk, PLACE_RIGHT, BLangue_fr, PLACE_UNDER, descriptif);
    SetWidgetPos(BAnnuler, PLACE_UNDER, BLangue_fr, NO_CARE, NULL);

   // SetWidgetPos(BErreurs, PLACE_UNDER, BAnnuler, NO_CARE, NULL);

    ShowDisplay();
    MainLoop();
}



/*
 * Menu "Aide" pour afficher les règles du jeu
*/

//static Widget explication;

void aide(Widget w, void *d){
    GetOkay(
    "Bienvenue dans le jeu du Pendu !\n\n"
    "Pour gagner, il faut trouver le mot a deviner, represente par les petits batons horizontaux "
    "(comme ca tu peux aussi connaitre le nombre de lettres). "
    "Selectionne les lettres grace a ton clavier !\n\n"
    "Si tu fais une erreur, le pendu se dessine petit a petit. "
    "Tu as un nombre maximum d'erreurs, que tu peux configurer dans le menu.\n\n"
    "Pour changer de langue, appuie sur le bouton en haut a gauche et selectionne ta langue favorite !\n\n"
    "Si tu veux en savoir plus sur le jeu, n'hesite pas a te rendre sur la page Wikipedia associee. \n"
    "Bonne chance !\n\n"
    );
    //MakeWindow("Aide", SAME_DISPLAY, EXCLUSIVE_WINDOW);
    //explication = MakeTextWidget("aide.txt", 0, 0, 300, 200);
    //Widget BOK = MakeButton("OK", annuler, NULL);
    //SetWidgetPos(explication, PLACE_UNDER, BOK, NO_CARE, NULL);
    //SetWidgetPos(BOK, PLACE_UNDER, explication, NO_CARE, NULL); // Bouton OK sous les explications
    //ShowDisplay();
    //MainLoop();
}
