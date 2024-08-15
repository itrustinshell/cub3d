#include "../cub3d.h"

int	routine_sectionX(t_c3d *c3d, t_ray *ray, char **map_grid, double alpha)
{
	printf("Routine SECTION_X\n");
	t_point end_point;
	int wall_check;

	end_point.x = 0;
	end_point.y = 0;
	wall_check = 0;
	end_point = get_end_point(c3d->player.position, c3d->map_fm_file.w,  alpha, ray, SECTION_X);
	wall_check = check_wall(end_point,  c3d, map_grid, ray);
	if (wall_check != OUTSIDE_PERIMETER)
	{
		if (wall_check == THROUGH_TWO_WALLS || wall_check == WALL_INTERCEPTED)
			return (0);
	}
	else
	{printf("Attenzione il raggio è andato oltre i confini della mappa!\n"); //ormai è fuori...devo trovare il punto di impatto sul muro quindi devo 
		increment_chosenPath_unitl_you_find_a_wall(ray,  alpha, c3d, end_point, PATH_Y);
		return (0); //serve a far interrompere il while esterno
	}
	return (1);
}

int	routine_sectionY(t_c3d *c3d, t_ray *ray, char **map_grid, double alpha)
{
	printf("Routine SECTION_Y\n");
	t_point end_point;
	int wall_check;

	end_point.x = 0;
	end_point.y = 0;
	wall_check = 0;

	end_point = get_end_point(c3d->player.position, c3d->map_fm_file.w, alpha,  ray, SECTION_Y);
	wall_check = check_wall(end_point,  c3d, map_grid, ray);
	if (wall_check != OUTSIDE_PERIMETER)
	{
		if (wall_check == THROUGH_TWO_WALLS || wall_check == WALL_INTERCEPTED)
			return (0);
	}
	else
	{	printf("Attenzione il raggio è andato oltre i confini della mappa!\n"); //ormai è fuori...devo trovare il punto di impatto sul muro quindi devo 
		increment_chosenPath_unitl_you_find_a_wall(ray, alpha, c3d, end_point, PATH_X);
		return (0); //serve a far interrompere il while esterno
	}
	return (1);
}
