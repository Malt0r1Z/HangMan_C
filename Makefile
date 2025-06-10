# ATTENTION CE SONT DES TAB ET NON DES ESPACES POUR LES 3 LIGNES
# décalées de ce fichier

# Variables
CC = gcc                     # Compilateur C
CFLAGS = -Wall               # Options de compilation (warnings)
LDFLAGS =                    # Options de l'éditeur de liens
SRC = callbacks.c data.c liste.c main.c readFile.c vue.c   # Fichiers sources
PROG = cal                   # Nom de l'exécutable
OBJS = $(SRC:.c=.o)          # Fichiers objets générés

.SUFFIXES: .c .o             # Extensions reconnues

# Cible par défaut
all: $(PROG)

# Édition de liens
$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^  # $@ = cible, $^ = dépendances

# Dépendances spécifiques
callbacks.o: callbacks.h data.h liste.h 
data.o: data.h readFile.h liste.h
liste.o: liste.h
# main.o: ?????
readFile.o: readFile.h liste.h
vue.o: vue.h data.h callbacks.h

# Règle générique pour compiler un .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Nettoyage
.PHONY: clean
clean:
	rm -f *.o *~ core $(PROG)
