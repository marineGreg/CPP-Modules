NAME        =	array

CXX         =	c++
CXXFLAGS    =	-Wall -Wextra -Werror -std=c++98

SRCS        =	main.cpp

# Transformation des .cpp en .o
OBJS        = $(SRCS:.cpp=.o)

# Règle par défaut
all: $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation terminée : $(NAME)"

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

.PHONY: all clean fclean re