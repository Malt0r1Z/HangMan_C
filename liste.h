//
//  liste.h
//  liste_version_prof
//
//  Created by Alex Meurillon on 25/04/2025.
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
//extern void supprimer(Liste *, const int);
//extern void supprimerEnQueue(Liste *);
//extern void supprimerEnQueueBis(Liste *);
