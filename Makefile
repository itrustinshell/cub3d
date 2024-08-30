NAME = cube

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(DIR)

SRC = 	c3d.c \
		ft_split.c \
		initializing/initializing.c \
		texture/texture_init.c \
		window/window.c \
		3d/manage_3d.c \
		closing_program/closing.c \
		moving/mov_update_all.c moving/mov_key_press.c moving/mov_key_release.c moving/mov_collision.c moving/mov_update_only_rotation.c moving/mov_update_only_position.c \
		drawing/drawing_2d_map.c drawing/drawing_3d.c drawing/drawing_player.c drawing/drawing_utils.c \
		dda/dda.c dda/dda_utils.c dda/delta_path_point.c dda/cardilnalDirection_sidePoint.c dda/checks.c dda/two_walls_check.c \
		map_building/read_the_map.c map_building/get_map_dimensions.c map_building/get_map_from_file.c map_building/create_visualize_map_img.c
		
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
