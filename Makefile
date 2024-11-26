NAME = cub3d
CC = gcc
CFLAGS = -I$(MLXDIR) #-Wall -Wextra -Werror

MLXDIR = ./mlx
MLXLIB = $(MLXDIR)/libmlx.a
INCLUDES = -I/usr/include -I$(MLXDIR) -O3
MLX_FLAGS = -L$(MLXDIR) -lmlx -L/usr/lib/X11 -lXext -lX11

SRCS = 	c3d.c \
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

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJDIR)
	make -C $(MLXDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(MLXDIR) clean
	
re: fclean all
