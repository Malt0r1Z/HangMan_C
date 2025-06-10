/*
 * main.c
 *
 * Khady DIOP & Alex MEURILLON ELSE3
*/



#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include "data.h"
#include "vue.h"

int main(int argc, char *argv[]) {
    if (OpenDisplay(argc, argv) == 0) {
      fprintf(stderr,"Can't open display\n");
      return EXIT_FAILURE;
    }
    // Initialisation de la partie avec le dictionnaire français
    Partie *jeu =  NULL;
    jeu =  init_Partie_fr();
    if (jeu == NULL) {
        fprintf(stderr, "Erreur lors de l'initialisation de la partie.\n");
        return EXIT_FAILURE;
    }

    // créer l'IG et l'afficher à l'écran
    init_display(argc, argv, &jeu);
    // Affichage du menu principal
    MainLoop();

    return EXIT_SUCCESS;
}