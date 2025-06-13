/*
 * main.c
 * Jeu du pendu
 * Khady DIOP & Alex MEURILLON ELSE3
 */

#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include "vue.h"
#include "data.h"
#include "callbacks.h"
Partie *jeu=NULL;
int main(int argc, char *argv[]) {
    // Initialisation de l'affichage (libsx)
    if (OpenDisplay(argc, argv) == 0) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir l'affichage.\n");
        return 1;
    }

    // Initialisation de la partie (jeu global défini dans callbacks.c)
    jeu=init_Partie_fr();
    // Création des widgets et de l'interface graphique
    init_display(argc, argv, NULL);

    // Lancement de la boucle principale d'événements
    MainLoop();

    return 0;
}