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

    // Création de l'interface graphique et affichage à l'écran
    init_display(argc, argv, NULL);
    // Affichage du menu principal
    MainLoop();

    return EXIT_SUCCESS;
}