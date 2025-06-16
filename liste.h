//
//  liste.h
//
//  Khady DIOP & Alex MEURILLON ELSE3
//

#pragma once

typedef void* T;

typedef struct noeud{
    T elt;
    struct noeud *suivant;
} *Liste;

extern Liste initListe(void);
extern int longueur(const Liste);
extern T ieme(const Liste, const int);
extern void inserer(Liste *, const int, const T);