#include "../cub3d.h"
#include <string.h>

double    calculation_of_temporarySX(t_c3d *c3d, t_ray *ray, double alpha)
{
    if (alpha == (M_PI / 2) || alpha == (3 * M_PI / 2))
        ray->SxTemp= ray->DyTemp / sin(alpha);
    else
        ray->SxTemp= ray->DxTemp / cos(alpha);
    if (fabs(ray->SxTemp) > (c3d->map_fm_file.w * TILE_SIZE))
        ray->SxTemp= c3d->map_fm_file.w * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
   // printf("ipotenusa tramite dx: %f\n", ray->SxTemp);
    return (ray->SxTemp);
}

double	calculation_of_temporarySY(t_c3d *c3d,  t_ray *ray, double alpha)
{
	if (alpha == (M_PI) || alpha == (2 * M_PI) || alpha == (0))
         ray->SyTemp = ray->DxTemp / cos(alpha);
	else
         ray->SyTemp = ray->DyTemp / sin(alpha);
	if (fabs( ray->SyTemp) > (c3d->map_fm_file.h * TILE_SIZE))
         ray->SyTemp = c3d->map_fm_file.h * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
  //  printf("ipotenusa tramite dy: %f\n",  ray->SyTemp);
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
    ray->end_point.x = ray->first_impact_point.x;
    ray->end_point.y = ray->first_impact_point.y;
    printf("INCREMENT cardinal: %s\n", ray->cardinal_direction);
    if (strcmp(ray->cardinal_direction, "NE") == 0) //per ora ho toloto E per questinoi di testing
    {
        printf("INIZIAAAA IL CONTROLLOOOO SU NE\n");
        printf("INCREMENT ray->sx = %f, ray->sy = %f\n", fabs(ray->sx), fabs(ray->sy));
        while (1)
        {
            if (fabs(ray->sx) < fabs(ray->sy))
            {   
                ray->DxTemp = abs(ray->dx) + TILE_SIZE;
                printf("INCREMENT ray->DxTemp = %d\n", ray->DxTemp);
                ray->SxTemp= calculation_of_temporarySX(c3d, ray, alpha);
                ray->end_point_to_check.x = c3d->player.x + fabs(ray->SxTemp) * cos(alpha);
                ray->end_point_to_check.y = c3d->player.y + fabs(ray->SxTemp) * sin(alpha);
                printf("INCREMENT ray->end_point_to_check.x = %d, ray->end_point_to_check.y = %d\n", ray->end_point_to_check.x, ray->end_point_to_check.y);
                printf("INCREMENT impact_tile: %d, %d\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
                //attenzione per far guardare al giusto quadrato ho sottratto -1 alle x quando è a NE. Non dovrebbe influire sul resto
                //inoltre attenzione questo -1 non cmbia le cooridnate di impatto ma agisce solo esternamente
                //cioè vede solo se la condizione di quella coordinata di impatto (che non varia) sottratta di uno
                //nella sua ascissa...ecc ecc...
                printf("vediamo ste coord siamo in sez x: %d, %d\n",ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);

                if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] != '1')
                {
            //  ray->DxTemp =  ray->dx + TILE_SIZE;
            // ray->sx  = calculate_sx(c3d, ray, alpha);
            // ray->end_point.x = c3d->player.x + fabs(ray->sx) * cos(alpha);
            // ray->end_point.y = c3d->player.y + fabs(ray->sx) * sin(alpha);
                    
                    ray->dx = ray->DxTemp; //aggiorno il ray->dx che mi servirà aggiornato per l'iterazione successiva
                    ray->sx = ray->SxTemp; //aggiorno per stesso motivo rigo precefente
                    ray->end_point.x = ray->end_point_to_check.x;
                    ray->end_point.y = ray->end_point_to_check.y;
                    bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                    printf("print along dist_x\n");
                }
                else
                {
                    printf("sez. x: abbiamo individuato un punto di impatto. procedo a verificare se ce ne sono di precedenti\n");
                    ray->dx = ray->DxTemp; //aggiorno il ray->dx che mi servirà aggiornato per l'iterazione successiva
                    ray->sx = ray->SxTemp; //aggiorno per stesso motivo rigo precefente
                    //verifico se dx è ancora minode di dy
                    if (fabs(ray->sx) > fabs(ray->sy)) //AAAA possiile frizione
                    {
                        ray->end_point.x = ray->end_point_to_check.x;
                        ray->end_point.y = ray->end_point_to_check.y;
                        bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                        printf("print alond d i s t _ X\n");
                        break;
                    }
                    else
                    {
                        while(fabs(ray->sx) > fabs(ray->sy))
                        {
                            ray->DxTemp = abs(ray->dx) + TILE_SIZE;
                            ray->SxTemp= calculation_of_temporarySX(c3d, ray, alpha);
                            ray->end_point_to_check.x = c3d->player.x + fabs(ray->SxTemp) * cos(alpha);
                            ray->end_point_to_check.y = c3d->player.y + fabs(ray->SxTemp) * sin(alpha);
                       
                            if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] != '1')
                            {
                                ray->dx = ray->DxTemp; //aggiorno il ray->dx che mi servirà aggiornato per l'iterazione successiva
                                ray->sx = ray->SxTemp; //aggiorno per stesso motivo rigo precefente
                                ray->end_point.x = ray->end_point_to_check.x;
                                ray->end_point.y = ray->end_point_to_check.y;
                                bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                            }
                            else
                            {
                                ray->dx = ray->DxTemp; //aggiorno il ray->dx che mi servirà aggiornato per l'iterazione successiva
                                ray->sx = ray->SxTemp; //aggiorno per stesso motivo rigo precefente
                                ray->end_point.x = ray->end_point_to_check.x;
                                ray->end_point.y = ray->end_point_to_check.y;
                                bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                                break;
                            }
                        }


                    }
                }
            }
            else
            {
                
                printf("Sez. Y\n");
                
                ray->DyTemp = abs(ray->dy) + TILE_SIZE; ///allora da questo memoento inzia qualcosa di anomalo che cambia dy..non la fa aumentare di TILE_SIZE
                printf("INCREMENT ray->DyTemp = %d\n", ray->DyTemp);
                ray->SyTemp = calculation_of_temporarySY(c3d, ray, alpha);
                ray->end_point_to_check.x = c3d->player.x + fabs(ray->SyTemp) * cos(alpha);
                ray->end_point_to_check.y = c3d->player.y + fabs(ray->SyTemp) * sin(alpha);
                printf("vediamo ste coord siamo in sez y\n");
                printf("INCREMENT ray->end_point_to_check.x = %d, ray->end_point_to_check.y = %d\n", ray->end_point_to_check.x, ray->end_point_to_check.y);
                printf("INCREMENT impact_tile: %d, %d\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
                if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] != '1')
                {
                    ray->dy = ray->DyTemp; //aggiorno il ray->dx che mi servirà aggiornato per l'iterazione successiva
                    ray->sy = ray->SyTemp; 
                    ray->end_point.x = ray->end_point_to_check.x;
                    ray->end_point.y = ray->end_point_to_check.y;
                    bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, GREEN);
                    printf("print along dist_y\n");
                }
                else
                {
                    printf("sex. y: abbiamo individuato un punto di impatto. procedo a verificare se ce ne sono di precedenti\n");
                    ray->dy = ray->DyTemp; //aggiorno il ray->dx che mi servirà aggiornato per l'iterazione successiva
                    ray->sy = ray->SyTemp; 
                    if (fabs(ray->sy) > fabs(ray->sx))
                    {
                        ray->end_point.x = ray->end_point_to_check.x;
                        ray->end_point.y = ray->end_point_to_check.y;
                        bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, GREEN);
                        break;
                    }
                    else
                    {
                        while(fabs(ray->sy) > fabs(ray->sx)) /// AAA punto frizione
                        {
                            ray->DyTemp = abs(ray->dy) + TILE_SIZE;
                            ray->SyTemp = calculation_of_temporarySX(c3d, ray, alpha);
                            ray->end_point_to_check.x = c3d->player.x + fabs(ray->SyTemp) * cos(alpha);
                            ray->end_point_to_check.y = c3d->player.y + fabs(ray->SyTemp) * sin(alpha);

                            if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] != '1')
                            {
                                ray->dy = ray->DyTemp; //aggiorno il ray->dx che mi servirà aggiornato per l'iterazione successiva
                                ray->sy = ray->SyTemp; //aggiorno per stesso motivo rigo precefente
                                ray->end_point.x = ray->end_point_to_check.x;
                                ray->end_point.y = ray->end_point_to_check.y;
                                bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                            }
                            else
                            {
                                ray->dy = ray->DyTemp; //aggiorno il ray->dx che mi servirà aggiornato per l'iterazione successiva
                                ray->sy = ray->SyTemp; //aggiorno per stesso motivo rigo precefente
                                ray->end_point.x = ray->end_point_to_check.x;
                                ray->end_point.y = ray->end_point_to_check.y;
                                bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                                break;
                            }
                        }
                
                    }
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