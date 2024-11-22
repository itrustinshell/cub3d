NAME = cube

CC = gcc
#CFLAGS = -Wall -Wextra -Werror -I$(DIR)

SRC = 	c3d.c \
		ft_split.c \
		initializing/initializing.c \
		texture/texture_init.c \
		window/window.c \
		3d_calculations/3d_calculations.c \
		closing_program/closing.c \
		moving/mov_update_all.c moving/mov_key_press.c moving/mov_key_release.c moving/mov_collision.c moving/mov_update_only_rotation.c moving/mov_update_only_position.c moving/mov_utils.c \
		drawing/drawing_2d_map.c drawing/drawing_routine.c drawing/drawing_player.c drawing/drawing_utils.c \
		drawing/drawing_3d/floor_and_ceiling.c drawing/drawing_3d/3d_fov.c drawing/drawing_3d/3d_scene.c\
		dda/dda.c dda/dda_utils.c dda/delta_path_point.c dda/cardilnalDirection_sidePoint.c dda/checks.c dda/two_walls_check.c \
		map_building/read_the_map.c map_building/get_map_dimensions.c map_building/get_map_from_file.c map_building/create_visualize_map_img.c
		
#SRC = main.c moving.c read_the_map.c get_map_dimensions.c get_map_from_file.c drawing.c
OBJ = $(SRC:.c=.o)

DIR = minilibx-linux

LIB = $(DIR)/libmlx.a

# Regola per compilare i file .c in file .o
# %.o: %.c
# $(CC) $(CFLAGS) -c $< -o $@
%.o: %.c
	$(CC) -I/usr/include -Imlx_linux -O3 -c $< -o $@


# Regola per creare l'eseguibile finale
# $(NAME): $(OBJ) $(LIB)
# 	$(CC) $(OBJ) -L$(DIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
# Regola per compilare la libreria MiniLibX

$(NAME): $(OBJ) $(LIB)
	$(CC) $(OBJ) -Lminilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)


$(LIB):
	make -C $(DIR)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(OBJ) -Lminilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)



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
