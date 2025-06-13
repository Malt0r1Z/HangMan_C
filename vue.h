/*
 * vue.h
 *
 * Khady Ndaye DIOP & Alex MEURILLON ELSE3
*/

#pragma once

extern void init_display(int, char *[], void *);
extern void DrawHangmanBase(Widget, int, int , void *);
extern void clearHangman(int);
extern void clearHangman();
extern void AfficherLettres();

extern Widget BMenu;
extern Widget BAide;


extern Widget ZoneLettres;
extern Widget ZoneSaisie;
extern Widget ZoneDessin ;