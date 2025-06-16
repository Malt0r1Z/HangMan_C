/*
 * Ce fichier callbacks.c contient toutes les fonctions de rappel 
 *
 * 
 * Ndeye khady DIOP & Alex MEURILLON ELSE3
*/

#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include <ctype.h>
#include "callbacks.h"
#include "data.h"
#include "vue.h"

// Pointeur vers la partie en cours, initialisé à NULL
Partie *jeu = NULL; 

// Pointeur pour stocker le choix de langue,français par defaut 
char *choix_langue = "francais"; 

//Widget static pour les descriptions
static Widget descriptif;

/*
 *  Rôle : Ferme la fenêtre courante 
*/
static void annuler(Widget w, void *d){
  CloseWindow();
}

/*
 * Rôle : Configure une partie avec le dictionnaire français et lance la partie
 *      Affiche un message de confirmation et relance le jeu avec la langue sélectionnée
*/
static void setLangue_fr(Widget w, void *d){
    choix_langue = "francais";
    GetOkay("Dictionnaire selectionnee : francais");
    rejouer(NULL, NULL);
}


/*
 * Rôle : Configure une partie avec  le dictionnaire  anglais  et lance la partie
 *      Affiche un message de confirmation et relance le jeu avec la langue sélectionnée
*/
static void setLangue_uk(Widget w, void *d){
  choix_langue = "Anglais";
  GetOkay("Dictionnaire selectionnee : anglais");
  rejouer(NULL, NULL);
}

/*
 * Rôle : Callback pour configurer la difficulté
*/
void bouton_cb(Widget w, void *d) {
  if (erreurs(jeu)>2){
    //le nombre d'erreurs doit etre inférieur ou égale à 2 pour modifier la difficulté
    GetOkay("Vous ne pouvez plus modifier le nombre d'erreurs maximum, "
      "car vous avez deja commence une partie.");
    CloseWindow();
  }
  else {
    //configurer la difficulté 
    char *difficulte = (char*)d;
    CloseWindow();
    setErreur(difficulte);
  }
}


/*
 * Rôle : Affiche à l'écran une fenêtre pour choisir le niveau de difficulté
 *        Crée une fenêtre avec 3 boutons (Facile/Moyen/Difficile)
 *        Chaque bouton déclenche bouton_cb() avec la difficulté correspondante
*/
void choix_difficulte(Widget w, void *d) {

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
Rôle : Initialisation du jeu en fonction du dictionnaire choisi
*/
void initGame() {
    // Libération de l'ancienne partie si elle existe
    if (jeu) {
      //Une partie existe déjà 
        quitter_partie(jeu);
        //La partie existante est libérée 
        jeu = NULL;
    }
    
    // Initialisation d'une nouvelle partie avec le bon dictionnaire 
    if (strcmp(choix_langue,"francais") == 0) {
        jeu = init_Partie_fr();
        //Une partie avec le dictionnaire français est initialisée
    }

    else {
        jeu = init_Partie_ang();
        // Une partie avec le dictionnaire uk est initialisée
    }
}


/*
 * Rôle : Réinitialise le jeu pour une nouvelle partie 
*/
void rejouer(Widget w, void *d){
    if (jeu) {
        //Presence d'une partie 
        quitter_partie(jeu);
        jeu = NULL;
    } // Libère la mémoire de la partie précédente avant d'en allouer à une nouvelle
    clearHangman(); // Efface le dessin du pendu
    initGame(); // Nouvelle partie est initialisée
    AfficherLettres(); // Mise à jour de l'affichage 
    SetStringEntry(ZoneSaisie, ""); // Efface la saisie
}

/*
 * Rôle : Affiche une fenêtre pour le choix des langues(menu) avec :
 *     * Un label descriptif
 *     * Boutons Français, Bouton Anglais et Bouton Annuler
*/
void menu(Widget w, void *d){
    // Logique pour afficher le menu :
    // Création de la fenêtre
    MakeWindow("Langues préférées", SAME_DISPLAY, EXCLUSIVE_WINDOW);


    // Création du label descriptif centré
    descriptif = MakeLabel("Selectionnez votre langue preferee :");
    SetWidgetPos(descriptif, PLACE_UNDER, w, NO_CARE, NULL);
   
    // Création des boutons pour la  sélection de la  langue
    Widget BLangue_fr = MakeButton("    Francais    ", setLangue_fr, NULL);
    Widget BLangue_uk = MakeButton("    Anglais    ", setLangue_uk, d);
    Widget BAnnuler = MakeButton("    Annuler    ", annuler, NULL);

    SetWidgetPos(BLangue_fr, PLACE_UNDER, descriptif, NO_CARE, NULL);
    // Bouton "Français" sous le label descriptif
    SetWidgetPos(BLangue_uk, PLACE_RIGHT, BLangue_fr, PLACE_UNDER, descriptif);
    // Bouton "Anglais" à droite du bouton Français
    SetWidgetPos(BAnnuler, PLACE_UNDER, BLangue_fr, NO_CARE, NULL);
    //Bouton Annuler sous le bouton Français


    ShowDisplay();
    MainLoop();
}


/*
 * Rôle: Menu "Aide" affiche les règles du jeu et ouvre l'URL dans le navigateur par défaut
*/
void aide(Widget w, void *d){
    GetOkay(
    "Bienvenue dans le jeu du Pendu !\n\n"
    "Pour gagner, il faut trouver le mot a deviner, represente par les petits batons horizontaux "
    "(comme ca tu peux aussi connaitre le nombre de lettres). "
    "Selectionne les lettres grace a ton clavier !\n\n"
    "Si tu fais une erreur, le pendu se dessine petit a petit. "
    "Tu as un nombre maximum d'erreurs, que tu peux configurer dans le menu.\n\n"
    "Pour changer de langue, appuie sur le bouton en haut a gauche et selectionne ta langue favorite !\n\n"
    "Si tu veux en savoir plus sur le jeu, n'hesite pas a te rendre sur la page Wikipedia ouverte dans ton navigateur. \n"
    "Bonne chance !\n\n"
    );
    system("xdg-open 'https://fr.wikipedia.org/wiki/Jeu_du_pendu' &");
}


/*
 * Rôle : Gère la saisie d'une lettre par le joueur lors de la partie 
 *        Si la partie est terminée => ignore la saisie
 *        Si caractère invalide => affiche un message d'erreur
 *        Si lettre valide => Met à jour l'état du jeu  Gère les deux cas (victoire ou défaite)
 * Antécédents : la partie doit être initialisée
 */
void saisie(Widget w, char* key , void *d) {
  if (terminee(jeu)){
    // La partie est terminée
    SetStringEntry(ZoneSaisie, ""); 
    // La saisie n'est pas prise en compte
   return; 
  }
  // La partie n'est pas terminée

  // Convertie la lettre en minuscule
  char lettre = tolower(key[0]);
  
  if (!isalpha(lettre)) {
    // Le boutton préssé sur le clavier n'est pas une lettre 
        GetOkay("Veuillez saisir une lettre a-z");
        // Message à l'utilisateur 
        SetStringEntry(ZoneSaisie, "");
        // La saisie n'est pas prise en compte
        return;
  }
  // L'utilisateur a saisi une lettre alphabétique
  else if ( key&&key[0]!= '\0') {
    int valide = validite_lettre(jeu,lettre);  // Met à jour le mot et les erreurs
    if (valide==2) {
      // La partie est terminée, le nombre d'erreurs maximum est atteint
      char message[256];
      snprintf(message, sizeof(message),
          "PERDU!!!\n\n"
          "En appuyant sur Okay, vous relancez une partie !\n\n"
          "Pour changer de langue, cliquez sur le bouton Menu en haut a gauche.\n\n"
          "Pour quitter le jeu, cliquez sur la croix en haut a droite.\n\n"
          "Le mot est : %s\n\n",
          get_mot_cherche(jeu)
      );
      GetOkay(message);
      // Message de fin de partie et possibilité de rejouer via le bouton OKAY
      SetStringEntry(ZoneSaisie, "");
       // La saisie n'est plus  prise en compte => fin de la partie 
      rejouer(w, d); // Relance une nouvelle partie
      return; 
    }

    AfficherLettres(); // Mettre à jour l'affichage du mot 
    SetStringEntry(ZoneSaisie, ""); // Vide la zone de saisie après chaque lettre
    // Mettre à jour la zone de dessin après chaque saisie
    updateDrawHangman(erreurs(jeu));

  }
   // La partie n'est pas perdue
   
  if (terminee(jeu) && gagnee(jeu)) {
    //la partie est terminée et l'utilisateur à gagnée la partie 
    char message_gagne[256];
    snprintf(message_gagne, sizeof(message_gagne),
        "BRAVO !!!! Vous avez gagné la partie  ! "
        "En appuyant sur Okay, vous relancez une partie !\n\n"
        "Pour changer de langue, cliquez sur le bouton Menu en haut a gauche.\n\n"
        "Pour quitter le jeu, cliquez sur la croix en haut a droite.\n\n"
        "Le mot est : %s\n\n",
        get_mot_cherche(jeu) );
      GetOkay(message_gagne);
      //Message de fin de partie et possibilité de rejouer via le bouton OKAY

    SetStringEntry(ZoneSaisie, ""); 
    //la saisie n'est plus prise en compte=>fin de la partie 

    rejouer(w, d); // Relance une nouvelle partie
    return; 
  }
}
  