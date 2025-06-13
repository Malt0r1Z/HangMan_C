/*
 * callbacks.h
 *
 *  Ndeye khady DIOP & Alex MEURILLON ELSE3
*/

#pragma once

extern void menu(Widget, void *);
extern void aide(Widget, void *);
extern void rejouer(Widget, void *);
extern void appliquer_erreur_max(Widget, void *);
extern void choix_difficulte(Widget, void *);
void saisie(Widget, char* , void *);
void initGame();
