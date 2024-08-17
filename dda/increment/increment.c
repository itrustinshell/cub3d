#include "../../cub3d.h"
#include <string.h>

void print_info(t_ray *ray, t_point first_point, t_point end_point)
{
	t_ray ciao;
	ciao = *ray;

	t_point ciaociao;
	ciaociao = end_point;
    printf("\n\n\n\n#### inizio controllo di increment ####\n");
    printf("la prima cella è: (%d, %d)\n", (int)first_point.x / TILE_SIZE, (int)first_point.y / TILE_SIZE);
    printf("la prima cella è stata incontrate nel punto: (%d, %d)\n", (int)first_point.x, (int)first_point.y);
}

t_point	increment(t_ray *ray, t_c3d *c3d, char **map_grid, double alpha) 
{
	ray->first_point.x = ray->first_impact_point.x; //associo il mio endpoin al primo punto di impatto. aggiornerò man mano il mio end point
	ray->first_point.y = ray->first_impact_point.y;
	print_info(ray, ray->first_point, ray->end_point);
	while (is_it_inside_map_perimeter(ray->first_point, c3d))
	{
		ray->first_side_point = chose_side_point(ray->first_point, ray->cardinal_direction); //individua uno dei vertici interni della cella
		ray->delta = calculate_delta(ray->first_point, ray->first_side_point, ray->cardinal_direction); //dx viene calcolato solo qui perchè poi saranno solo incrementi fissi di TILE_SIZE
		ray->path = calculate_path(ray->delta, alpha);
		if (fabs(ray->path.x) < fabs(ray->path.y))
		{
			printf("si sono entrato in x\n");
			ray->end_point = trigonometric_pointCalculation(ray->first_point, ray->path.x, alpha);
		}
		else
			ray->end_point = trigonometric_pointCalculation(ray->first_point, ray->path.y, alpha);
		if (is_it_a_wall(ray->end_point, map_grid))
		{
			bresenham(c3d, c3d->player.position.x, c3d->player.position.y, ray->end_point.x, ray->end_point.y, BLACK);
			break;
		}
		else
			ray->first_point = ray->end_point;
	}
	return (ray->end_point);  //da oscurare se attivi la parte sotto
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