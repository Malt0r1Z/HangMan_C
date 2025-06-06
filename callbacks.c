/*
 * callbacks.c
 *
 * Khady Ndaye DIOP & Alex MEURILLON ELSE3
*/

#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include "callbacks.h"



/*
 * Menu pour changer de langue 
*/
static Widget descriptif;

static void annuler(Widget w, void *d){
  CloseWindow();
}

static void setLangue_fr(Widget w, void *d){
  printf("Langue française sélectionnée\n");
  // Logique pour changer la langue en français
  CloseWindow();
}

static void setLangue_uk(Widget w, void *d){
  printf("Langue anglaise sélectionnée\n");
  // Logique pour changer la langue en anglais
  CloseWindow();
}

void menu(Widget w, void *d){
    printf("Menu button cliqué\n");
    // Logique pour afficher le menu :
    MakeWindow("Langues préférées", SAME_DISPLAY, EXCLUSIVE_WINDOW);
    descriptif = MakeLabel("Sélectionnez votre langue préférée :");
    SetWidgetPos(descriptif, PLACE_ABOVE, w, NO_CARE, NULL);
    Widget BLangue_fr = MakeButton("Annuler", setLangue_fr, NULL);
    Widget BLangue_uk = MakeButton("Valider", setLangue_uk, d);
    SetWidgetPos(BLangue_fr, PLACE_UNDER, entree, NO_CARE, NULL);
    SetWidgetPos(BLangue_uk, PLACE_RIGHT, BLangue_fr, PLACE_UNDER, entree);
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

/*
 * Rejouer pour recommencer une partie
*/

void rejouer(Widget w, void *d){
    printf("Rejouer button cliqué\n");
    initGame(); // Réinitialiser le jeu
    CloseWindow();
}