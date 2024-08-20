#include "../cub3d.h"

t_point get_circumference_point(t_point player_next_position, double angle)
{
    t_point circumference_point;

    circumference_point.x = 0;
    circumference_point.y = 0;
    circumference_point.x = player_next_position.x + RADIUS * cos(angle);
    circumference_point.y = player_next_position.y + RADIUS * sin(angle);
    return (circumference_point);
}

  
int is_collision(double player_next_x, double player_next_y, t_c3d *c3d) 
{
    t_point player_next_position;
    t_point circumference_point;
    double angle;
    int i;
    player_next_position.x = player_next_x;
    player_next_position.y = player_next_y;

    circumference_point.x = 0;
    circumference_point.y = 0;
    i = 0; 
    while (i < CIRCUMFERENCE_CHECKS) 
    {
        angle = 2 * M_PI * i / CIRCUMFERENCE_CHECKS; 
        circumference_point = get_circumference_point(player_next_position, angle);
       // point_along_circumference.y = circumference_y(player_next_y, angle) / TILE_SIZE; 
        printf("If you do another step in this direction you will be in grid: %d, %d\n", c3d->map_fm_file.x, c3d->map_fm_file.y);
        if (is_it_inside_map_perimeter(circumference_point, c3d->map_fm_file.dimension)) 
        {
            if (is_it_a_wall(circumference_point, c3d->map_fm_file.grid))
                return (1);
        }
        else
            return (1);
        i++;
    }
    return (0);
}
