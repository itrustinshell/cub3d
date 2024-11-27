NAME = cub3d
CC = gcc
CFLAGS = -I$(MLXDIR) -Iincludes -I$(LIBFTDIR) -g #-Wall -Wextra -Werror

MAP_PATH = res/maps/map.cub
EXE = $(NAME) $(MAP_PATH)

LIBFTDIR = ./libft
LIBFT = ./libft/libft.a

MLXDIR = ./mlx
MLXLIB = $(MLXDIR)/libmlx.a
INCLUDES = -I/usr/include -I$(MLXDIR) -O3
MLX_FLAGS = -L$(MLXDIR) -lmlx -L/usr/lib/X11 -lXext -lX11

SRCS = 	srcs/main.c \
		srcs/utils/closing.c srcs/utils/3d_calculations.c srcs/utils/utils.c srcs/utils/testing.c \
		srcs/utils/initializing/initializing.c srcs/utils/initializing/initializing2.c \
		srcs/moving/mov_update_all.c srcs/moving/mov_key_press.c srcs/moving/mov_key_release.c srcs/moving/mov_update_only_position.c \
		srcs/moving/utils/moving_main_direction.c srcs/moving/utils/moving_oblq_direction.c srcs/moving/utils/mov_collision.c \
		srcs/drawing/drawing_2d_map.c srcs/drawing/drawing_player.c srcs/drawing/drawing_utils.c \
		srcs/drawing/drawing_3d/3d_fov.c srcs/drawing/drawing_3d/3d_scene.c \
		srcs/drawing/map_building/build_map.c srcs/drawing/map_building/get_map_from_file.c \
		srcs/dda/dda.c srcs/dda/delta_path_point.c srcs/dda/cardilnalDirection_sidePoint.c \
		srcs/dda/utils/dda_utils.c srcs/dda/utils/dda_checks.c
		
OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

all: $(MLXLIB) $(NAME)

$(LIBFT):
	$(MAKE) all -C $(LIBFTDIR)

$(MLXLIB):
	make -C $(MLXDIR)

$(NAME): $(OBJS) $(LIBFT)
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
	make -C $(LIBFTDIR) clean 
	make -C $(MLXDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C .$(LIBFTDIR) fclean 
	make -C $(MLXDIR) clean
	
re: fclean all
