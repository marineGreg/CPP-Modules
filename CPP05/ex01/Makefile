# Nom de l'exécutable
NAME        =	bureaucrats

# Compilateur et Flags
CXX         =	c++
CXXFLAGS    =	-Wall -Wextra -Werror -std=c++98

# Fichiers sources (à adapter selon l'exercice)
SRCS        =	main.cpp Bureaucrat.cpp

# Transformation des .cpp en .o
OBJS        = $(SRCS:.cpp=.o)

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
	@echo "Fichiers objets supprimés."

# Nettoyage complet (objets + exécutable)
fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) supprimé."

# Re-compilation totale
re: fclean all

# Empêche la confusion avec des fichiers du même nom
.PHONY: all clean fclean re