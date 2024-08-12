#include "../cub3d.h"
#include <string.h>

double    calculation_of_temporarySX(t_c3d *c3d, t_ray *ray, double alpha)
{
    if (alpha == (M_PI / 2) || alpha == (3 * M_PI / 2))
        ray->SxTemp = ray->DyTemp / sin(alpha);
    else
        ray->SxTemp = ray->DxTemp / cos(alpha);
    if (fabs(ray->SxTemp) > (c3d->map_fm_file.w * TILE_SIZE))
        ray->SxTemp= c3d->map_fm_file.w * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
    printf("calculation temporarySX %f\n", fabs(ray->SxTemp));
    return (fabs(ray->SxTemp));
}

double	calculation_of_temporarySY(t_c3d *c3d,  t_ray *ray, double alpha)
{
	if (alpha == (M_PI) || alpha == (2 * M_PI) || alpha == (0))
         ray->SyTemp = ray->DxTemp / cos(alpha);
	else
        ray->SyTemp = ray->DyTemp / sin(alpha);
	if (fabs(ray->SyTemp) > (c3d->map_fm_file.h * TILE_SIZE))
         ray->SyTemp = c3d->map_fm_file.h * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
    printf("calculation temporarySY %f\n",  fabs(ray->SyTemp));
	return ( fabs(ray->SyTemp));
}

//dato una certa ipotenusa Sx ottenuta mediante un aumento con Dx mi calcolo i punti estremi della fine di Sx laddove il punto di partenza è smepre il player
void calculation_of_end_point_to_check_along_SxTemp(t_c3d *c3d, t_ray *ray, double alpha)
{
    ray->DxTemp = abs(ray->dx) + TILE_SIZE; //allora aumentiamo di TILE_SIZE il dx. Andiamo a salvare questo valroe in un DXtemporaneo
    printf("DxTemp = %d\n", ray->DxTemp);
    ray->SxTemp = calculation_of_temporarySX(c3d, ray, alpha);     //grazie al dx_temporaneo calcolato possiamo calcolarci il nuovi SXtemporaneo           
    ray->end_point_to_check.x = c3d->player.x + fabs(ray->SxTemp) * cos(alpha); //grazie al calcolo del sx temporaneo ecco che posso calcoalrre il nuovo punto
    ray->end_point_to_check.y = c3d->player.y + fabs(ray->SxTemp) * sin(alpha);
    printf("end_point_to_check: (%d, %d)\n", ray->end_point_to_check.x, ray->end_point_to_check.y);
    printf("cella di impatto: %d, %d\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
}

//dato una certa ipotenusa Sy ottenuta mediante un aumento con Dy mi calcolo i punti estremi della fine di Sy laddove il punto di partenza è smepre il player
void calculation_of_end_point_to_check_along_SyTemp(t_c3d *c3d, t_ray *ray, double alpha)
{
    ray->DyTemp = abs(ray->dy) + TILE_SIZE; //aumento di TILE_SIZE
    printf("DyTemp = %d\n", ray->DyTemp);
    ray->SyTemp = calculation_of_temporarySY(c3d, ray, alpha);
    ray->end_point_to_check.x = c3d->player.x + fabs(ray->SyTemp) * cos(alpha);
    ray->end_point_to_check.y = c3d->player.y + fabs(ray->SyTemp) * sin(alpha);
    printf("end_point_to_check:(%d, %d)\n", ray->end_point_to_check.x, ray->end_point_to_check.y);
    printf("cella di impatto:: %d, %d\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);             
}

void print_info(t_ray *ray)
{
    printf("\n\n\n\n#### inizio controllo di increment ####\n");
    printf("dx iniziale = %d\n", ray->dx);
    printf("dy iniziale = %d\n", ray->dy);
    printf("la prima cella è: (%d, %d)\n", ray->end_point.x / TILE_SIZE, ray->end_point.y / TILE_SIZE);
    printf("la prima cella è stata incontrate nel punto: (%d, %d)\n", ray->end_point.x, ray->end_point.y);
}

/*gli passo un punto per frlo verificare. Se il muro ha attraversato due muri, setta il corrispettivo end_point
da stampare  e ritprna 1 per fare il break.

vedere poi se è megliofare una eventuale verisone che mette piu precisione magari con double
sulla mappa*/
int is_it_passing_between_two_walls(t_c3d *c3d, t_ray *ray, t_point point)
{
    if (c3d->map_fm_file.grid[point.y / TILE_SIZE][((point.x - 1) / TILE_SIZE)] == '1' && c3d->map_fm_file.grid[(point.y + 1) / TILE_SIZE][(point.x / TILE_SIZE)] == '1')
    {
        printf("ma attenzione che le celle affianco sono muri!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        ray->end_point.x = point.x - 1;
        ray->end_point.y = point.y + 1;
        printf("le cooridnate di impatto sono: %d, %d\n", ray->end_point.x, ray->end_point.y);
        bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, YELLOW);
        return (1);
    }
    return (0);
}

int is_it_a_wall_for_increment_x(t_c3d *c3d, t_ray *ray)
{
    if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] != '1')
    {        
        printf("NO! La cella (%d, %d) NON è un muro\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
        ray->dx = ray->DxTemp; //aggiorno il ray->dx che mi servirà aggiornato per l'iterazione successiva
        ray->sx = ray->SxTemp; //aggiorno per stesso motivo rigo precefente
        ray->end_point.x = ray->end_point_to_check.x; //aggiorno il punto finale
        ray->end_point.y = ray->end_point_to_check.y;
        return (0);
    }
    else
    {
        printf("Si! La cella (%d, %d) è un muro\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
        ray->end_point.x = ray->end_point_to_check.x;
        ray->end_point.y = ray->end_point_to_check.y;
        printf("le cooridnate di impatto sono: %d, %d\n", ray->end_point_to_check.x, ray->end_point_to_check.y);
        bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, BLUE);
        return (1);
    }
    return (0);
}

int is_it_a_wall_for_increment_y(t_c3d *c3d, t_ray *ray)
{
    if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] != '1')
    {
        printf("NO! La cella (%d, %d) NON è un muro\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
        ray->dy = ray->DyTemp; //aggiorno il ray->dx che mi servirà aggiornato per l'iterazione successiva
        ray->sy = ray->SyTemp; 
        ray->end_point.x = ray->end_point_to_check.x;
        ray->end_point.y = ray->end_point_to_check.y;
        return (0);
    }
    else
    {
        printf("Si! La cella (%d, %d) è un muro\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
        ray->end_point.x = ray->end_point_to_check.x;
        ray->end_point.y = ray->end_point_to_check.y;
        bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
        return (1);
    }
}

int	is_it_inside_map_perimeter(t_point point, t_c3d *c3d)
{
	if (point.x >= 0 && point.x < c3d->map_fm_file.w * TILE_SIZE && point.y >= 0 && point.y < (c3d->map_fm_file.h * TILE_SIZE) - TILE_SIZE)
		return (1);
	else
		return (0);
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
				// if (is_it_inside_map_perimeter(ray->end_point_to_check, c3d))
				// {
					if (is_it_passing_between_two_walls(c3d, ray, ray->end_point_to_check))
						break;
					if (is_it_a_wall_for_increment_y(c3d, ray))
						break;
				// }
				// else
				// {

				// }

			}
		}
	}
	else
	{
		bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, BLACK);
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