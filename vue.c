/*
 * vue.c
 *
 * Khady Ndaye DIOP & Alex MEURILLON ELSE3
*/

#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include "data.h"
#include "callbacks.h"

#define LARGEUR_FENETRE 600
#define HAUTEUR_FENETRE 400
#define TAILLE_ZONE_LETTRES 300


// Callback pour dessiner le pendu 
void DrawHangman(Widget w, int width, int height, void *data) {
    DrawCircle(w, width/2, height/3, 30); // Tête du pendu
    DrawLine(w, width/2, height/3 + 30, width/2, height/3 + 100); // Corps
    DrawLine(w, width/2, height/3 + 50, width/2 - 30, height/3 + 80); // Bras gauche
    DrawLine(w, width/2, height/3 + 50, width/2 + 30, height/3 + 80); // Bras droit
    DrawLine(w, width/2, height/3 + 100, width/2 - 30, height/3 + 130); // Jambe gauche
    DrawLine(w, width/2, height/3 + 100, width/2 + 30, height/3 + 130); // Jambe droite
}

// Fonction pour afficher les lettres à deviner 
void AfficherLettres(Widget w, char *mot, int *lettres_trouvees) {
    printf("Mot à deviner : ");
}

// Rôle: création et assemblage des widgets 
void init_display(int argc, char *argv[], void *d) {

    Widget 
        ZoneDessin, // Zone pour dessiner le pendu
        ZoneLettres,// Zone pour afficher les lettres à deviner
        BMenu,      // le bouton Menu pour accéder au menu
        BAide,      // le bouton Aide pour afficher l'aide
        BRejouer;   // le bouton Rejouer pour recommencer une partie

    // Création des boutons
    BMenu = MakeButton("Menu", menu_cb, d);
    BAide = MakeButton("Aide", aide_cb, d);

    // Zone de dessin centrale pour le pendu
    ZoneDessin = MakeDrawArea(LARGEUR_FENETRE, 200, DrawHangman, d);

    // Zone pour les lettres à deviner, centrée sous le pendu
    ZoneLettres = MakeLabel("A _ _ _ _ _ Z"); // À remplacer dynamiquement

    // Placement des widgets
    // Ligne du haut : Menu à gauche, Aide à droite
    SetWidgetPos(BMenu,  PLACE_ABOVE, ZoneDessin, NO_CARE, NULL);
    SetWidgetPos(BAide,  PLACE_RIGHT, ZoneDessin, PLACE_ABOVE, ZoneDessin);

    // Zone de dessin centrée (par défaut, premier widget)
    // Zone des lettres sous la zone de dessin, centrée
    SetWidgetPos(ZoneLettres, PLACE_UNDER, ZoneDessin, NO_CARE, NULL);

    // Couleurs et affichage
    GetStandardColors();
    ShowDisplay();
}