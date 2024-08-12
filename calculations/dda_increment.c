#include "../cub3d.h"
#include <string.h>

void print_info(t_ray *ray)
{
    printf("\n\n\n\n#### inizio controllo di increment ####\n");
    printf("dx iniziale = %d\n", ray->dx);
    printf("dy iniziale = %d\n", ray->dy);
    printf("la prima cella è: (%d, %d)\n", (int)ray->end_point.x / TILE_SIZE, (int)ray->end_point.y / TILE_SIZE);
    printf("la prima cella è stata incontrate nel punto: (%d, %d)\n", (int)ray->end_point.x, (int)ray->end_point.y);
}

void	increment(t_ray *ray, t_c3d *c3d, double alpha) //# NOTA_2
{
	ray->end_point.x = ray->first_impact_point.x; //associo il mio endpoin al primo punto di impatto. aggiornerò man mano il mio end point
	ray->end_point.y = ray->first_impact_point.y;
	print_info(ray);
	if (strcmp(ray->cardinal_direction, "NE") == 0) //per ora ho toloto E per questinoi di testing
	{
		printf("INIZIAAAA IL CONTROLLOOOO SU NE\n");
		while (1)
		{
			if (is_it_passing_between_two_walls(c3d, ray, ray->first_impact_point)) //il primo punto che arriva da reaching_the_side è un muro?
				break;
			printf("sx = %f, sy = %f\n", fabs(ray->sx), fabs(ray->sy));
			if (fabs(ray->sx) < fabs(ray->sy)) //se sx reale è più piccolo di sy reale
			{   
				printf("sez. x:\n");
				calculation_of_end_point_to_check_along_SxTemp(c3d, ray, alpha);
				if (is_it_inside_map_perimeter(ray->end_point_to_check, c3d)) //#NOTA 1
				{
					if (is_it_passing_between_two_walls(c3d, ray, ray->end_point_to_check))
						break;
					if (is_it_a_wall_for_increment_x(c3d, ray))
						break;
				}
				else
				{
					printf("Attenzione il raggio è andato oltre i confini della mappa!\n"); //ormai è fuori...devo trovare il punto di impatto sul muro quindi devo 
					while (1) //quindi aumento di volta in volta lungo la y fino a quando non incontro un muro.
					{
						calculation_of_end_point_to_check_along_SyTemp(c3d, ray, alpha); //ovvimente questa funzione aumenta sempre di un TILE_sIZE il dyTemporary
						if (is_it_a_wall_for_increment_y(c3d, ray))
							break;
					}
					break; //serve a far interrompere il while esterno
				}
			}
			else
			{
				printf("Sez. Y\n");
				calculation_of_end_point_to_check_along_SyTemp(c3d, ray, alpha);
				    if (is_it_inside_map_perimeter(ray->end_point_to_check, c3d))
				    {
                        if (is_it_passing_between_two_walls(c3d, ray, ray->end_point_to_check))
                            break;
                        if (is_it_a_wall_for_increment_y(c3d, ray))
                            break;
				    }
				    else
                    {
					printf("Attenzione il raggio è andato oltre i confini della mappa!\n"); //ormai è fuori...devo trovare il punto di impatto sul muro quindi devo 
					while (1) //quindi aumento di volta in volta lungo la x fino a quando non incontro un muro.
					{
						calculation_of_end_point_to_check_along_SxTemp(c3d, ray, alpha); //ovvimente questa funzione aumenta sempre di un TILE_sIZE il dyTemporary
						if (is_it_a_wall_for_increment_x(c3d, ray))
							break;
					}
					break; //serve a far interrompere il while esterno

                    }

			}
		}
	}
	else
	{
		bresenham(c3d, c3d->player.coordinates.x, c3d->player.coordinates.y, ray->end_point.x, ray->end_point.y, BLACK);
		printf ("print_you are not pointing NE\n");
	}
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