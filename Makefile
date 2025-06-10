# ATTENTION CE SONT DES TAB ET NON DES ESPACES POUR LES 3 LIGNES
# décalées de ce fichier

# Variables
CC = gcc                     # Compilateur C
CFLAGS = -g -Wall               # Options de compilation (warnings)
LDFLAGS = -lsx                   # Options de l'éditeur de liens
SRC = callbacks.c data.c hangman.c liste.c readFile.c vue.c   # Fichiers sources
PROG = hangman                   # Nom de l'exécutable
OBJS = $(SRC:.c=.o)          # Fichiers objets générés

.SUFFIXES: .c .o             # Lien entre les suffixes

# Cible par défaut
all: $(PROG)

# étapes de compilation et d'édition de liens
# $@ la cible  $^ toutes les dépendances	
$(PROG): $(OBJS)
	$(CC)  -o $@ $^ $(LDFLAGS)

# Dépendances spécifiques
callbacks.o: callbacks.h data.h liste.h 
data.o: data.h readFile.h liste.h
liste.o: liste.h
hangman.o: data.h vue.h
readFile.o: readFile.h liste.h
vue.o: vue.h data.h callbacks.h

# Règle générique pour compiler un .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Nettoyage
.PHONY: clean
clean:
	rm -f *.o *~ core $(PROG)
