#include "../cub3d.h"

static int  circumference_x(int player_next_x, double angle)
{
    int circumference_x;

    circumference_x = player_next_x + RADIUS * cos(angle);
    printf("circumference_x %d\n", circumference_x);
    return circumference_x;
}

static int  circumference_y(int player_next_y, double angle)
{
    int circumference_y;

    circumference_y = player_next_y + RADIUS * sin(angle);
    printf("circumference_y %d\n", circumference_y);
    return circumference_y;
}
  
int is_collision(int player_next_x, int player_next_y, t_c3d *c3d) 
{
    double angle;
    int i;

    i = 0; 
    while (i < CIRCUMFERENCE_CHECKS) 
    {
        angle = 2 * M_PI * i / CIRCUMFERENCE_CHECKS; 
        c3d->map_fm_file.x = circumference_x(player_next_x, angle) / TILE_SIZE;
        c3d->map_fm_file.y = circumference_y(player_next_y, angle) / TILE_SIZE; 
        printf("If you do another step in this direction you will be in grid: %d, %d\n", c3d->map_fm_file.x, c3d->map_fm_file.y);
        if (c3d->map_fm_file.x >= 0 && c3d->map_fm_file.x < c3d->map_fm_file.dimension.width && c3d->map_fm_file.y >= 0 && c3d->map_fm_file.y < c3d->map_fm_file.dimension.heigth) 
        {
            if (c3d->map_fm_file.grid[c3d->map_fm_file.y][c3d->map_fm_file.x] == '1')
                return (1);
        }
        else
            return (1);
        i++;
    }
    return (0);
}