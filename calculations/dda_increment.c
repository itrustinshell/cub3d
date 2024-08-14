#include "../cub3d.h"
#include <string.h>

void print_info(t_ray *ray)
{
    printf("\n\n\n\n#### inizio controllo di increment ####\n");
    printf("dx iniziale = %f\n", ray->initialDx);
    printf("dy iniziale = %f\n", ray->initialDy);
    printf("la prima cella è: (%d, %d)\n", (int)ray->end_point.x / TILE_SIZE, (int)ray->end_point.y / TILE_SIZE);
    printf("la prima cella è stata incontrate nel punto: (%d, %d)\n", (int)ray->end_point.x, (int)ray->end_point.y);
}


t_point trigonometric_pointCalculation(t_point player_position, double path, double alpha)
{
	t_point point_to_return;

	point_to_return.x = 0;
	point_to_return.y = 0;
	point_to_return.x = player_position.x + round(fabs(path) * cos(alpha)); //grazie al calcolo del sx temporaneo ecco che posso calcoalrre il nuovo punto
	point_to_return.y = player_position.y + round(fabs(path) * sin(alpha)); printf("end_point_to_check: (%d, %d)\n", (int)point_to_return.x, (int)point_to_return.y);printf("cella di impatto: %d, %d\n", (int)point_to_return.x / TILE_SIZE, (int)point_to_return.y / TILE_SIZE);
	return (point_to_return);
}


int check_wall(t_point end_point, t_c3d *c3d, char **map_grid, t_ray *ray)
{
	if (is_it_inside_map_perimeter(end_point, c3d)) //#NOTA 1
	{
		if (is_it_passing_between_two_walls(c3d, ray, map_grid, end_point)) 
			return (THROUGH_TWO_WALLS);
		if (is_it_a_wall(map_grid, end_point, c3d))
		{
			bresenham(c3d, c3d->player.position.x, c3d->player.position.y, end_point.x, end_point.y, PINK);
			return (WALL_INTERCEPTED);
		}
		return (INSIDE_PERIMETER);
	}
	else
		return (OUTSIDE_PERIMETER);
	return (OUTSIDE_PERIMETER);
}




void	increment_chosenPath_unitl_you_find_a_wall(t_ray *ray, double alpha, t_c3d *c3d, t_point end_point, int chose_path)
{
	while (WALL_IS_NOT_INTERCEPTED) //quindi aumento di volta in volta lungo la y fino a quando non incontro un muro.
	{
		if (chose_path == PATH_X)
		{
			ray->dx = fabs(ray->dx) + TILE_SIZE; 
			ray->path_x =  calculate_path(c3d->map_fm_file.w, ray->dx, ray->dy, alpha, PATH_X);     //grazie al dx_temporaneo calcolato possiamo calcolarci il nuovi path_xoraneo           
			end_point = trigonometric_pointCalculation(c3d->player.position, ray->path_x, alpha) ;//ovvim
		}
		else
		{
			ray->dy = fabs(ray->dy) + TILE_SIZE;
			ray->path_y =  calculate_path(c3d->map_fm_file.w, ray->dx, ray->dy, alpha, PATH_Y); 
			end_point = trigonometric_pointCalculation(c3d->player.position, ray->path_y, alpha);//ovvimente questa funzione aumenta sempre di un TILE_sIZE il dyTemporary
		}
		if (is_it_a_wall(c3d->map_fm_file.grid, end_point, c3d))
		{
			bresenham(c3d, c3d->player.position.x, c3d->player.position.y, end_point.x, end_point.y, PINK);
			break;
		}
	}
	return;
}

t_point get_end_point(t_point player_position, int map_length, double alpha, t_ray *ray, int chose_section_x_or_y)
{
	t_point end_point;
	if (chose_section_x_or_y == SECTION_X)
	{
		ray->dx = fabs(ray->dx) + TILE_SIZE; 
		ray->path_x =  calculate_path(map_length, ray->dx, ray->dy, alpha, PATH_X);     //grazie al dx_temporaneo calcolato possiamo calcolarci il nuovi path_xoraneo           
		end_point = trigonometric_pointCalculation(player_position, ray->path_x, alpha); //ovvim
	}
	else
	{
		ray->dy = fabs(ray->dy) + TILE_SIZE;
		ray->path_y =  calculate_path(map_length, ray->dx, ray->dy, alpha, PATH_Y); 
		end_point = trigonometric_pointCalculation(player_position, ray->path_y, alpha);
	}
	return (end_point);
}



t_point	increment(t_ray *ray, t_c3d *c3d, char **map_grid, double alpha) //# NOTA_2
{
	t_point end_point;

	end_point.x = ray->first_impact_point.x; //associo il mio endpoin al primo punto di impatto. aggiornerò man mano il mio end point
	end_point.y = ray->first_impact_point.y;
	print_info(ray);

	if (strcmp(ray->cardinal_direction, "NE") == 0) //per ora ho toloto E per questinoi di testing
	{
		int wall_check; printf("INIZIAAAA IL CONTROLLOOOO SU NE\n");
		while (1)
		{
			if (is_it_passing_between_two_walls(c3d, ray, map_grid, end_point)) //il primo punto che arriva da reaching_the_side è un muro?
				break;  printf("sx = %f, sy = %f\n", fabs(ray->path_x), fabs(ray->path_y));
			if (fabs(ray->path_x) < fabs(ray->path_y)) //se sx reale è più piccolo di sy reale
			{   printf("sez. x:\n");
				end_point = get_end_point(c3d->player.position, c3d->map_fm_file.w,  alpha, ray, SECTION_X);
				wall_check = check_wall(end_point,  c3d, map_grid, ray);
				if (wall_check != OUTSIDE_PERIMETER)
				{
					if (wall_check == THROUGH_TWO_WALLS || wall_check == WALL_INTERCEPTED)
						break;
				}
				else
				{printf("Attenzione il raggio è andato oltre i confini della mappa!\n"); //ormai è fuori...devo trovare il punto di impatto sul muro quindi devo 
					increment_chosenPath_unitl_you_find_a_wall(ray,  alpha, c3d, end_point, PATH_Y);
					break; //serve a far interrompere il while esterno
				}
			}
			else
			{printf("Sez. Y\n");
				ray->dy = fabs(ray->dy) + TILE_SIZE;
				ray->path_y =  calculate_path(c3d->map_fm_file.w, ray->dx, ray->dy, alpha, PATH_Y);
				end_point = trigonometric_pointCalculation(c3d->player.position, ray->path_y, alpha);; //ovvimente questa funzione aumenta sempre di un TILE_sIZE il dyTemporary
				wall_check = check_wall(end_point,  c3d, map_grid, ray);
				if (wall_check != OUTSIDE_PERIMETER)
				{
					if (wall_check == THROUGH_TWO_WALLS || wall_check == WALL_INTERCEPTED)
						break;
				}
				else
				{	printf("Attenzione il raggio è andato oltre i confini della mappa!\n"); //ormai è fuori...devo trovare il punto di impatto sul muro quindi devo 
					increment_chosenPath_unitl_you_find_a_wall(ray, alpha, c3d, end_point, PATH_X);
					break; //serve a far interrompere il while esterno
				}
			}
		}
	}
	else
	{
		bresenham(c3d, c3d->player.position.x, c3d->player.position.y, end_point.x, end_point.y, BLACK);
		printf ("print_you are not pointing NE\n");
	}
	return (end_point);
}

/* #NOTA_1 
ECCO trovato il segmentation fault. 
In questo punto del codice ho un punto che ho appena trova.
devo trovare un modo per gestirlo. potrei dire che quando la cella di impatto arriva a tali coordinate 
allora deve fermarsi nella iterazione. cioè non deve reiterare la y o la x oltre i limiti dellamappa...che è poi l'iterazione che stavo costruendo nella
parte finale del ray casting. Quindi un while in cui dico itera fino a quando i valori non hanno superato i confini della mappa o quando sono muri.
Però ora ho messo un if e sta andando.
##########################*/

//AAAAAA is >= ????? verifiy!!
/* #NOTA_2
progpbelam individuato: quando incrementa di un certo deltax o deltay
io gli dico che se il punto di impatto che vien fuori è un muro allora stampa fin li e 
breack. Ma è sbagliato. Deve avvenire infatti un ultimo check, ovvero bisogna vedere se dopo quell'incremento dx o dy
il corrispettivo path sul ray è ancora minore rispetto all'altro (path).
Se è ancora minore allora può finire il tutto.
Se è diventato maggiore bisogna controllare l'altro ....perchè potrebbe esserci un punto di impatto di lato sul quadrato
quindi fino a che l'altro resta piu piccolo lo si aumenta finchè non incontra un mro. 
*/