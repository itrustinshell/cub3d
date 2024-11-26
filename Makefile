NAME = cub3d
CC = gcc
CFLAGS = -I$(MLXDIR) -Iincludes #-Wall -Wextra -Werror

MAP_PATH = srcs/map_building/map.cub
EXE = $(NAME) $(MAP_PATH)

MLXDIR = ./mlx
MLXLIB = $(MLXDIR)/libmlx.a
INCLUDES = -I/usr/include -I$(MLXDIR) -O3
MLX_FLAGS = -L$(MLXDIR) -lmlx -L/usr/lib/X11 -lXext -lX11

SRCS = 	srcs/main.c \
		srcs/utils/ft_split.c \
		srcs/initializing/initializing.c \
		srcs/texture/texture_init.c \
		srcs/window/window.c \
		srcs/3d_calculations/3d_calculations.c \
		srcs/closing_program/closing.c \
		srcs/moving/mov_update_all.c srcs/moving/mov_key_press.c srcs/moving/mov_key_release.c srcs/moving/mov_collision.c srcs/moving/mov_update_only_rotation.c srcs/moving/mov_update_only_position.c srcs/moving/mov_utils.c \
		srcs/drawing/drawing_2d_map.c srcs/drawing/drawing_routine.c srcs/drawing/drawing_player.c srcs/drawing/drawing_utils.c \
		srcs/drawing/drawing_3d/floor_and_ceiling.c srcs/drawing/drawing_3d/3d_fov.c srcs/drawing/drawing_3d/3d_scene.c\
		srcs/dda/dda.c srcs/dda/dda_utils.c srcs/dda/delta_path_point.c srcs/dda/cardilnalDirection_sidePoint.c srcs/dda/checks.c srcs/dda/two_walls_check.c \
		srcs/map_building/read_the_map.c srcs/map_building/get_map_dimensions.c srcs/map_building/get_map_from_file.c srcs/map_building/create_visualize_map_img.c
		
OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

all: $(MLXLIB) $(NAME)

$(MLXLIB):
	make -C $(MLXDIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) -lm -lz

test: all
	./$(EXE)

norm:
	norminette $(SRCS) includes
	
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXE)

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJDIR)
	make -C $(MLXDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(MLXDIR) clean
	
re: fclean all
