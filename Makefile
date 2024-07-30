NAME = cube

SRC = cub3d.c read_the_map.c get_map_dimensions.c get_map_from_file.c drawing.c
#SRC = main.c read_the_map.c get_map_dimensions.c get_map_from_file.c drawing.c
OBJ = $(SRC:.c=.o)

DIR = minilibx
LIB = $(DIR)/libmlx.a

# Regola per compilare i file .c in file .o
%.o: %.c
	$(CC) -Wall -Wextra -Werror -I$(DIR) -c $< -o $@

# Regola per creare l'eseguibile finale
$(NAME): $(OBJ) $(LIB)
	$(CC) $(OBJ) -L$(DIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# Regola per compilare la libreria MiniLibX
$(LIB):
	make -C $(DIR)

# Regola per pulire i file oggetto e i file della libreria
clean:
	rm -f $(OBJ)
	make -C $(DIR) clean

# Regola per pulire tutto, inclusa l'eseguibile
fclean: clean
	rm -f $(NAME)
	make -C $(DIR) clean

# Regola per ricompilare tutto
re: fclean all
