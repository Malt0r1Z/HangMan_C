/*
 * vue.c
 *
 * Khady DIOP & Alex MEURILLON ELSE3
*/

#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include "data.h"
#include "callbacks.h"
#include "vue.h"

#define LARGEUR_FENETRE 600
#define HAUTEUR_FENETRE 400
#define TAILLE_ZONE_LETTRES 300

extern Partie *jeu;
Widget ZoneDessin;
Widget ZoneSaisie;
Widget ZoneLettres;


// Callback pour dessiner le pendu 
void DrawHangman(Widget w, int width, int height, void *data) {
    // Support du pendu (à gauche)
    int base_x = width/4;
    int base_y = height/6;
    int poteau_haut = base_y;
    int poteau_bas = height - 5;

    // Base horizontale (Sol)
    DrawLine(base_x - 40, poteau_bas, base_x + 40, poteau_bas);
    // Poteau vertical
    DrawLine(base_x, poteau_bas, base_x, poteau_haut); 
    // Barre horizontale supérieure
    DrawLine(base_x, poteau_haut, width/2, poteau_haut); 
    // Barre pour soutenir le support
    DrawLine(base_x + 20, poteau_bas, base_x, poteau_bas - 50);
    // Petite barre verticale (corde)
    DrawLine(width/2, poteau_haut, width/2, height/3);


    // Tête du pendu sous forme de cercle 
    DrawArc(width/2 - 15, height/3, 30, 30, 0, 360);
    DrawLine(width/2, height/3 + 30, width/2, height/3 + 100); // Corps
    DrawLine(width/2, height/3 + 50, width/2 - 30, height/3 + 80); // Bras gauche
    DrawLine(width/2, height/3 + 50, width/2 + 30, height/3 + 80); // Bras droit
    DrawLine(width/2, height/3 + 100, width/2 - 30, height/3 + 130); // Jambe gauche
    DrawLine(width/2, height/3 + 100, width/2 + 30, height/3 + 130); // Jambe droite
}



// Fonction pour afficher les lettres à deviner 
void AfficherLettres(void) {
    if (jeu && ZoneLettres) {
        const char *etat = mot_en_cours(jeu);
        SetLabel(ZoneLettres, (char *)etat);
    }
}
// Rôle: création et assemblage des widgets 
void init_display(int argc, char *argv[], void *d) {

    Widget 
       // ZoneDessin, // Zone pour dessiner le pendu
       // ZoneLettres,// Zone pour afficher les lettres à deviner
        BMenu,      // le bouton Menu pour accéder au menu
        BSetErreur, // le bouton pour configurer le nombre d'erreurs
        BAide,      // le bouton Aide pour afficher l'aide
        BRejouer,   // le bouton Rejouer pour recommencer une partie
        LabelZone;
    // Création des boutons
    BMenu = MakeButton("Menu", menu, d);
    BSetErreur = MakeButton("Niveau de difficulte", choix_difficulte, d);
    BAide = MakeButton("Aide", aide, d);
    BRejouer = MakeButton("Rejouer", rejouer, d);

    // Placement des widgets
    // Nous utilisons des Widgets Espace afin de placer les widgets à notre guise
    Widget Espace_haut = MakeButton("                                            ", NULL, NULL); // Espaces
    Widget Espace_bas = MakeButton("                                   ", NULL, NULL); // Espaces
    // Ligne du haut : Menu à gauche, Aide à droite, Rejouer à droite de Aide
    SetWidgetPos(BMenu,  NO_CARE, NULL, NO_CARE, NULL);
    SetWidgetPos(BSetErreur, PLACE_RIGHT, BMenu, NO_CARE, NULL);
    SetWidgetPos(Espace_haut, PLACE_RIGHT, BSetErreur, NO_CARE, NULL);
    SetWidgetPos(BAide,  PLACE_RIGHT, Espace_haut, NO_CARE, NULL);
    SetWidgetPos(BRejouer, PLACE_RIGHT, BAide, NO_CARE, NULL);

    // Zone de dessin centrale pour le pendu
    ZoneDessin = MakeDrawArea(LARGEUR_FENETRE, 200, DrawHangman, d);
    SetWidgetPos(ZoneDessin, PLACE_UNDER, BMenu, NO_CARE, NULL);


    // Zone pour les lettres à deviner, centrée sous le pendu
    ZoneSaisie=MakeStringEntry(NULL, 100, saisie, d);
  

    GetStandardColors();
    int fond_saisie = GetRGBColor(220, 200, 220);  // RGB entre 0-255
    SetBgColor(ZoneSaisie, fond_saisie);

    ZoneLettres = MakeLabel(" _ _ _ _ _ _"); 
    XFont font = GetFont("12x24");  // Pour augmenter l'affichage du mot
    SetWidgetFont(ZoneLettres, font);
    LabelZone=MakeLabel("Saisir une lettre :");
     SetWidgetFont(LabelZone, font);
    // Zone des lettres sous la zone de dessin, centrée horizontalement
    SetWidgetPos(LabelZone,PLACE_UNDER,ZoneLettres,NO_CARE,NULL);
    SetWidgetPos(ZoneSaisie, PLACE_UNDER, ZoneLettres, PLACE_RIGHT, LabelZone);
    SetWidgetPos(Espace_bas, NO_CARE, NULL, PLACE_UNDER, ZoneDessin);
    SetWidgetPos(ZoneLettres, PLACE_RIGHT, Espace_bas, PLACE_UNDER, ZoneDessin);
    SetWidgetSize(ZoneLettres, 300, 50);

    // Couleurs et affichage
    GetStandardColors();
    ShowDisplay();
}
