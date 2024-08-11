#include "../cub3d.h"
#include <string.h>



void dda(t_c3d *c3d)
{
    t_ray   ray;

    ray.left_alpha = c3d->player.alpha_direction - 8 * DEGREE;
    ray.right_alpha = c3d->player.alpha_direction + 8 * DEGREE;

    printf("ecco l'anfgolo: %f\n", c3d->player.alpha_direction);
    get_cardinal_direction(c3d->player.alpha_direction, &ray);
    reaching_first_side(c3d, &ray, c3d->player.alpha_direction);
    if (c3d->map_fm_file.grid[ray.first_impact_point.y / TILE_SIZE][ray.first_impact_point.x / TILE_SIZE] == '1')
    {
      bresenham(c3d, c3d->player.x, c3d->player.y, ray.first_impact_point.x, ray.first_impact_point.y, YELLOW);
   // if (c3d->map_fm_file.grid[ray.first_impact_point.y / TILE_SIZE][ray.first_impact_point.x / TILE_SIZE] != '1')
    }
    else
    {
          increment(&ray, c3d, c3d->player.alpha_direction);
    }
    // else
    // {
    //     bresenham(c3d, c3d->player.x, c3d->player.y, ray.first_impact_point.x, ray.first_impact_point.y, PURPLE);
    //     printf("print initial impact point\n");
    // }
  // printf("iamm bell: %d, %d\n", ray.end_point.x / TILE_SIZE, ray.end_point.y / TILE_SIZE);
  //  printf("ecco ray.dx dopo increment: %d\n", ray.dx);

   // printf("next point %d,%d\n", ray.end_point.x, ray.end_point.y);
  

  
    // if (c3d->map_fm_file.grid[ray.end_point.y / TILE_SIZE][ray.end_point.x / TILE_SIZE] != '1')
    // {
   // }
     //   bresenham(c3d, c3d->player.x, c3d->player.y, ray.end_point.x, ray.end_point.y, WHITE);


// while (ray.left_alpha < ray.right_alpha)
// {
// printf("ecco l'anfgolo: %f\n", c3d->player.alpha_direction);
//     ray.cardinal_direction = get_cardinal_direction(ray.left_alpha , &ray);
// printf("ecco la stringa: %s\n", ray.cardinal_direction);
//     ray.first_impact_point = reaching_first_side(c3d, &ray, ray.left_alpha );
//     bresenham(c3d, c3d->player.x, c3d->player.y, ray.first_impact_point.x, ray.first_impact_point.y, WHITE);
// ray.left_alpha += DEGREE;
// }
}


/*
il ritorno di dda
lo passo a bresenam per fargli disegnare la linea
void draw_line(void *mlx, void *win, int x0, int y0, double alpha, int color) 

*/