#include "../cub3d.h"
#include <string.h>

double    calculation_of_temporarySX(t_c3d *c3d, t_ray *ray, double alpha)
{
    if (alpha == (M_PI / 2) || alpha == (3 * M_PI / 2))
        ray->SxTemp = ray->DyTemp / sin(alpha);
    else
        ray->SxTemp= ray->DxTemp / cos(alpha);
    if (fabs(ray->SxTemp) > (c3d->map_fm_file.w * TILE_SIZE))
        ray->SxTemp= c3d->map_fm_file.w * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
    printf("calculation temporarySX %f\n", ray->SxTemp);
    return (ray->SxTemp);
}

double	calculation_of_temporarySY(t_c3d *c3d,  t_ray *ray, double alpha)
{
	if (alpha == (M_PI) || alpha == (2 * M_PI) || alpha == (0))
         ray->SyTemp = ray->DxTemp / cos(alpha);
	else
        ray->SyTemp = ray->DyTemp / sin(alpha);
	if (fabs(ray->SyTemp) > (c3d->map_fm_file.h * TILE_SIZE))
         ray->SyTemp = c3d->map_fm_file.h * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
    printf("calculation temporarySY %f\n",  ray->SyTemp);
	return ( ray->SyTemp);
}

//AAAAAA is >= ????? verifiy!!
/*
progpbelam individuato: quando incrementa di un certo deltax o deltay
io gli dico che se il punto di impatto che vien fuori è un muro allora stampa fin li e 
breack. Ma è sbagliato. Deve avvenire infatti un ultimo check, ovvero bisogna vedere se dopo quell'incremento dx o dy
il corrispettivo path sul ray è ancora minore rispetto all'altro (path).
Se è ancora minore allora può finire il tutto.
Se è diventato maggiore bisogna controllare l'altro ....perchè potrebbe esserci un punto di impatto di lato sul quadrato
quindi fino a che l'altro resta piu piccolo lo si aumenta finchè non incontra un mro. 
*/
void increment(t_ray *ray, t_c3d *c3d, double alpha)
{
    //associo il mio endpoin al primo punto di impatto.
    //aggiornerò man mano il mio end point
    printf("\n\n\n\n#### inizio controllo di increment ####\n");
    ray->end_point.x = ray->first_impact_point.x;
    ray->end_point.y = ray->first_impact_point.y;
    printf("dx iniziale = %d\n", ray->dx);
    printf("dy iniziale = %d\n", ray->dy);
    printf("la prima cella è: (%d, %d)\n", ray->end_point.x / TILE_SIZE, ray->end_point.y / TILE_SIZE);
    printf("la prima cella è stata incontrate nel punto: (%d, %d)\n", ray->end_point.x, ray->end_point.y);

    if (strcmp(ray->cardinal_direction, "NE") == 0) //per ora ho toloto E per questinoi di testing
    {
        printf("INIZIAAAA IL CONTROLLOOOO SU NE\n");
        while (1)
        {
            printf("sx = %f, sy = %f\n", fabs(ray->sx), fabs(ray->sy));
            if (fabs(ray->sx) < fabs(ray->sy))
            {   
                printf("sez. x:\n");
                ray->DxTemp = abs(ray->dx) + TILE_SIZE;
                printf("DxTemp = %d\n", ray->DxTemp);

                ray->SxTemp = calculation_of_temporarySX(c3d, ray, alpha);               
                ray->end_point_to_check.x = c3d->player.x + fabs(ray->SxTemp) * cos(alpha);
                ray->end_point_to_check.y = c3d->player.y + fabs(ray->SxTemp) * sin(alpha);
        
                printf("end_point_to_check: (%d, %d)\n", ray->end_point_to_check.x, ray->end_point_to_check.y);
                printf("cella di impatto: %d, %d\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
/*#################ECCO trovato il segmentation fault 
devo trovare un modo per gestirlo. potrei dire che quando la cella di impatto arriva a tali coordinate 
allora deve fermarsi nella iterazione. cioè non deve reiterare la y o la x oltre i limiti dellamappa...che è poi l'iterazione che stavo costruendo nella
parte finale del ray casting. Quindi un while in cui dico itera fino a quando i valori non hanno superato i confini della mappa o quando sono muri.
##########################*/
if (ray->end_point_to_check.x >= 0 && ray->end_point_to_check.x <= c3d->map_fm_file.w * TILE_SIZE && ray->end_point_to_check.y >= 0 && ray->end_point_to_check.y <= c3d->map_fm_file.h * TILE_SIZE)
{
    printf("ok o ok ok ok ok ok ok ok ok ok ok \n");
}   
else
{
    printf("AAAAAAAAAAAAAAAA EXIT\n");
    exit(1);
}
                if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][((ray->end_point_to_check.x - 1) / TILE_SIZE)] == '1' && c3d->map_fm_file.grid[(ray->end_point_to_check.y + 1) / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] == '1')
                {
                    printf("ma attenzione che le celle affianco sono muri!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                    ray->end_point.x = ray->end_point_to_check.x - 1;
                    ray->end_point.y = ray->end_point_to_check.y + 1;
                    printf("le cooridnate di impatto sono: %d, %d\n", ray->end_point_to_check.x, ray->end_point_to_check.y);

                    bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                    break ;
                }
                if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] != '1')
                {        
                    printf("NO! La cella (%d, %d) NON è un muro\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);

                    ray->dx = ray->DxTemp; //aggiorno il ray->dx che mi servirà aggiornato per l'iterazione successiva
                    ray->sx = ray->SxTemp; //aggiorno per stesso motivo rigo precefente
                    ray->end_point.x = ray->end_point_to_check.x; //aggiorno il punto finale
                    ray->end_point.y = ray->end_point_to_check.y;
                  //  bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                }
                else
                {
                    printf("Si! La cella (%d, %d) è un muro\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
                    ray->end_point.x = ray->end_point_to_check.x;
                    ray->end_point.y = ray->end_point_to_check.y;
                    printf("le cooridnate di impatto sono: %d, %d\n", ray->end_point_to_check.x, ray->end_point_to_check.y);

                    bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                    break ;
                }
            }
            else
            {
                printf("Sez. Y\n");
                ray->DyTemp = abs(ray->dy) + TILE_SIZE; ///allora da questo memoento inzia qualcosa di anomalo che cambia dy..non la fa aumentare di TILE_SIZE
                printf("DyTemp = %d\n", ray->DyTemp);
                ray->SyTemp = calculation_of_temporarySY(c3d, ray, alpha);
                ray->end_point_to_check.x = c3d->player.x + fabs(ray->SyTemp) * cos(alpha);
                ray->end_point_to_check.y = c3d->player.y + fabs(ray->SyTemp) * sin(alpha);
                printf("end_point_to_check:(%d, %d)\n", ray->end_point_to_check.x, ray->end_point_to_check.y);
                printf("cella di impatto:: %d, %d\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
                if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] != '1')
                {
                    printf("NO! La cella (%d, %d) NON è un muro\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
                    ray->dy = ray->DyTemp; //aggiorno il ray->dx che mi servirà aggiornato per l'iterazione successiva
                    ray->sy = ray->SyTemp; 
                    ray->end_point.x = ray->end_point_to_check.x;
                    ray->end_point.y = ray->end_point_to_check.y;
                 //   bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, WHITE);
                }
                else
                {
                    printf("Si! La cella (%d, %d) è un muro\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
                    ray->end_point.x = ray->end_point_to_check.x;
                    ray->end_point.y = ray->end_point_to_check.y;
                    bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, WHITE);
                    break;
                }
            }
        }
    }
    else
    {
        bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, BLACK);
        printf ("print_you are not pointing NE\n");
    }
}