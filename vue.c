//
// vue.c
// 
// Khady DIOP & Alex MEURILLON ELSE3
//
// Ce fichier implémente la vue du jeu de pendu

#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include "data.h"
#include "callbacks.h"
#include "vue.h"


// Définitions d'une constante pour la taille de la fenêtre
#define LARGEUR_FENETRE 600

// Déclaration de la variable globale pour la partie en cours et des widgets
extern Partie *jeu;
Widget ZoneDessin;
Widget ZoneSaisie;
Widget ZoneLettres;


/*
 * Rôle : Callback pour dessiner le support du pendu
*/
static void DrawHangmanBase(Widget w, int width, int height, void *data) {
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
}

/*
 * Rôle : Fonction pour dessiner le pendu en fonction du nombre d'erreurs
 * Antécédent : La zone de dessin doit être créée et affichée
*/
void updateDrawHangman(int erreurs) {
    int erreur = erreurs;
    int width, height;
    getDrawAreaSize(&width, &height); // Récupère la taille de la zone de dessin pour rendre le dessin responsive

    if (erreur >=1) DrawArc(width/2 - 15, height/3, 30, 30, 0, 360); // Tête du pendu sous forme de cercle 
    if (erreur >=2) DrawLine(width/2, height/3 + 30, width/2, height/3 + 100); // Corps
    if (erreur >=3) DrawLine(width/2, height/3 + 50, width/2 - 30, height/3 + 80); // Bras gauche
    if (erreur >=4) DrawLine(width/2, height/3 + 50, width/2 + 30, height/3 + 80); // Bras droit
    if (erreur >=5) DrawLine(width/2, height/3 + 100, width/2 - 30, height/3 + 130); // Jambe gauche
    if (erreur >=6) DrawLine(width/2, height/3 + 100, width/2 + 30, height/3 + 130); // Jambe droite
    if (erreur >=7) DrawLine(width/2 - 7, height/3 + 10, width/2 - 3, height/3 + 10); // Oeil gauche
    if (erreur >=8) DrawLine(width/2 + 3, height/3 + 10, width/2 + 7, height/3 + 10); // Oeil droit
}

/*
 * Rôle : Efface le dessin du pendu
 * Antécédent : Le widget doit être créé et affiché
*/
void clearHangman(void) {
    ClearDrawArea(); // Efface la zone de dessin
    // Redessine la base du pendu
    int width, height;
    getDrawAreaSize(&width, &height); // Récupère la taille de la zone de dessin pour rendre le dessin responsive
    DrawHangmanBase(ZoneDessin, width, height, NULL);
}


/*
 * Rôle : Callback pour gérer l'affichage des lettres saisies
 * Antécédent : La zone de lettres doit être créée et affichée
*/
void AfficherLettres(void) {
    if (jeu && ZoneLettres) {
        const char *etat = mot_en_cours(jeu);
        SetLabel(ZoneLettres, (char *)etat);
    }
}

/*
 * Rôle : Initialise l'affichage du jeu
 * Conséquent : Crée les widgets, les boutons et les zones de saisie
*/
void init_display(int argc, char *argv[], void *d) {
    initGame(); // Initialisation d'une seule partie au démarrage

    Widget
        BMenu,      // Bouton Menu pour accéder au menu
        BSetErreur, // Bouton pour configurer le nombre d'erreurs
        BAide,      // Bouton Aide pour afficher l'aide
        BRejouer,   // Bouton Rejouer pour recommencer une partie
        LabelZone;  // Label pour indiquer la zone de saisie des lettres

    // Création des boutons
    BMenu = MakeButton("Menu", menu, d);
    BSetErreur = MakeButton("Niveau de difficulte", choix_difficulte, d);
    BAide = MakeButton("Aide", aide, d);
    BRejouer = MakeButton("Rejouer", rejouer, d);

    // Placement des widgets
    // Nous utilisons des Widgets Espace afin de placer les widgets à notre guise
    Widget Espace_haut = MakeButton("                                            ", NULL, NULL); // Espaces
    Widget Espace_bas = MakeButton("                      ", NULL, NULL); // Espaces
    // Ligne du haut : Menu à gauche suivi du menu de difficulté. Aide à droite et bouton Rejouer après l'Aide
    SetWidgetPos(BMenu,  NO_CARE, NULL, NO_CARE, NULL);
    SetWidgetPos(BSetErreur, PLACE_RIGHT, BMenu, NO_CARE, NULL);
    SetWidgetPos(Espace_haut, PLACE_RIGHT, BSetErreur, NO_CARE, NULL);
    SetWidgetPos(BAide,  PLACE_RIGHT, Espace_haut, NO_CARE, NULL);
    SetWidgetPos(BRejouer, PLACE_RIGHT, BAide, NO_CARE, NULL);

    // Zone de dessin centrale pour le pendu
    ZoneDessin = MakeDrawArea(LARGEUR_FENETRE, 200, DrawHangmanBase, d);
    SetWidgetPos(ZoneDessin, PLACE_UNDER, BMenu, NO_CARE, NULL);


    // Zone pour les lettres à deviner, centrée sous le pendu
    ZoneSaisie=MakeStringEntry(NULL, 100, saisie, d);
  

    // Couleurs et affichage des boutons
    int fond_saisie = GetRGBColor(220, 200, 220);  // Fond violet clair 
    int fond_boutons = GetRGBColor(153, 204, 255); // Fond bleu clair 
    SetBgColor(BMenu, fond_boutons); // Couleur de fond du bouton Menu
    SetBgColor(BSetErreur, fond_boutons); // Couleur de fond du choix de difficulté
    SetBgColor(BAide, fond_boutons); // Couleur de fond du bouton Aide
    SetBgColor(BRejouer, fond_boutons); // Couleur de fond du bouton Rejouer
    SetBgColor(ZoneSaisie, fond_saisie); // Couleur de fond de la zone de saisie

    // Zone de lettres pour afficher le mot en cours
    // Initalisation de la zone de lettres avec le mot en cours ou des tirets si pas de mot
    char *debut = strdup(jeu?mot_en_cours(jeu):"______");
    ZoneLettres = MakeLabel(debut);
    free(debut);  

    // Taille de la police pour la zone de lettres et le label
    XFont font = GetFont("12x24");  // Augmente la taille d'affichage du mot
    SetWidgetFont(ZoneLettres, font);
    LabelZone=MakeLabel("Saisir une lettre :");
    SetWidgetFont(LabelZone, font);


    // Zone des lettres sous la zone de dessin, centrée horizontalement
    SetWidgetPos(LabelZone, PLACE_UNDER, ZoneLettres, NO_CARE, NULL);
    SetWidgetPos(ZoneSaisie, PLACE_UNDER, ZoneLettres, PLACE_RIGHT, LabelZone);
    SetWidgetPos(Espace_bas, NO_CARE, NULL, PLACE_UNDER, ZoneDessin);
    SetWidgetPos(ZoneLettres, PLACE_RIGHT, Espace_bas, PLACE_UNDER, ZoneDessin);
    SetWidgetSize(ZoneLettres, 300, 50);

    // Couleurs et affichage
    GetStandardColors();
    ShowDisplay();
}
