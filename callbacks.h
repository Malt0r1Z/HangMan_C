/*
 * callbacks.h
 *
 *  Ndeye khady DIOP & Alex MEURILLON ELSE3
*/

#pragma once

extern void menu(Widget, void *);
extern void aide(Widget , void *);
extern void rejouer(Widget , void *);
void appliquer_erreur_max(Widget , void *);
extern void erreur(Widget w, void *);
extern void setLangue_fr(Widget , void *);
extern void setLangue_uk(Widget , void *);
extern void annuler(Widget, void *);
void initGame();