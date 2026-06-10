# Nom de l'exécutable
NAME        = polymorphism

# Compilateur et Flags
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98

# Fichiers sources (à adapter selon l'exercice)
SRCS        = main.cpp \

# Transformation des .cpp en .o
OBJS        = $(SRCS:.cpp=.o)

# Couleurs pour le terminal (optionnel mais stylé pour l'éval)
GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m

# Règle par défaut
all: $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN) Compilation terminée : $(NAME)$(RESET)"

# Compilation des fichiers objets
%.o: %.cpp
	@echo " Compilation de $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@rm -f $(OBJS)
	@echo "$(RED) Fichiers objets supprimés.$(RESET)"

# Nettoyage complet (objets + exécutable)
fclean: clean
	@rm -f $(NAME)
	@echo "$(RED) $(NAME) supprimé.$(RESET)"

# Re-compilation totale
re: fclean all

# Empêche la confusion avec des fichiers du même nom
.PHONY: all clean fclean re