# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -O2

# Nom de l'exécutable
TARGET = ifshow

# Répertoire source
SRC_DIR = src

# Fichier source
SRC = $(SRC_DIR)/ifshow.c

# Règle par défaut
all: $(TARGET)

# Règle pour compiler l'exécutable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(TARGET)

# Règle pour installer l'exécutable dans /usr/local/bin
install:
	cp $(TARGET) /usr/local/bin/

# Règle pour désinstaller l'exécutable
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Indique que "clean", "install" et "uninstall" ne sont pas des fichiers
.PHONY: all clean install uninstall