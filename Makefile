NAME = cube

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(DIR)

SRC = 	c3d.c \
		initializing/initializing.c \
		moving/moving.c moving/moving_utils_press_release_position.c moving/moving_utils_press_release_rotation.c moving/moving_utils_collision.c moving/moving_utils_update_rotation.c moving/moving_utils_update_position.c \
		drawing/drawing.c drawing/drawing_player.c \
		dda/dda.c \
		dda/initial_operations/initial_delta.c dda/initial_operations/direction_sidePoint_reachingFirstSide.c \
		dda/increment/increment.c dda/increment/routine.c dda/increment/increment_calculations.c \
		dda/general_calculations_and_checks/path.c dda/general_calculations_and_checks/pointCalculation.c dda/general_calculations_and_checks/checks.c \
		map_building/read_the_map.c map_building/get_map_dimensions.c map_building/get_map_from_file.c

#SRC = main.c moving.c read_the_map.c get_map_dimensions.c get_map_from_file.c drawing.c
OBJ = $(SRC:.c=.o)

DIR = minilibx

LIB = $(DIR)/libmlx.a

# Regola per compilare i file .c in file .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


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
	
all: $(NAME)

# Regola per ricompilare tutto
re: fclean all
