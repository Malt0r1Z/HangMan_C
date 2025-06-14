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

int main(int argc, char *argv[]) {
    
    if (OpenDisplay(argc, argv) == 0) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir l'affichage.\n");
        return 1;
    }
      
    init_display(argc, argv, NULL);
    MainLoop();
    return 0;
}