# Nom du compilateur
CXX = g++

# Options de compilation
CXXFLAGS = -std=c++17 -Wall

# Répertoire pour les fichiers source
SRCDIR = src

# Répertoire pour les fichiers objets
OBJDIR = obj

# Répertoire pour l'exécutable
BINDIR = bin

# Liste des fichiers source (recherche tous les fichiers .cpp dans le répertoire SRCDIR)
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Générer la liste des fichiers objets à partir des fichiers sources
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Nom de l'exécutable
TARGET = $(BINDIR)/JustRelax

# Options de lien pour la bibliothèque SDL2
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

# Règle de construction de l'exécutable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Règle pour générer les fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers temporaires
clean:
	rm -rf $(OBJDIR)