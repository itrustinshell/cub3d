#include "../cub3d.h"
#include <string.h>

double    calculation_of_temporarySX(t_c3d *c3d, t_ray *ray, double alpha)
{
    if (alpha == (M_PI / 2) || alpha == (3 * M_PI / 2))
        ray->SxTemporary = ray->DeltaYTemp / sin(alpha);
    else
        ray->SxTemporary= ray->DeltaXTemp / cos(alpha);
    if (fabs(ray->SxTemporary) > (c3d->map_fm_file.w * TILE_SIZE))
        ray->SxTemporary= c3d->map_fm_file.w * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
   // printf("ipotenusa tramite delta_x: %f\n", ray->SxTemporary);
    return (ray->SxTemporary);
}

double	calculation_of_temporarySY(t_c3d *c3d,  t_ray *ray, double alpha)
{
	if (alpha == (M_PI) || alpha == (2 * M_PI) || alpha == (0))
         ray->SyTemporary = ray->DeltaXTemp / cos(alpha);
	else
        ray->SyTemporary = ray->DeltaYTemp / sin(alpha);
	if (fabs(ray->SyTemporary) > (c3d->map_fm_file.h * TILE_SIZE))
         ray->SyTemporary = c3d->map_fm_file.h * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
  //  printf("ipotenusa tramite delta_y: %f\n",  ray->SyTemporary);
	return ( ray->SyTemporary);
}

//AAAAAA is >= ????? verifiy!!
/*
progpbelam individuato: quando incrementa di un certo deltax o deltay
io gli dico che se il punto di impatto che vien fuori è un muro allora stampa fin li e 
breack. Ma è sbagliato. Deve avvenire infatti un ultimo check, ovvero bisogna vedere se dopo quell'incremento delta_x o delta_y
il corrispettivo path sul ray è ancora minore rispetto all'altro (path).
Se è ancora minore allora può finire il tutto.
Se è diventato maggiore bisogna controllare l'altro ....perchè potrebbe esserci un punto di impatto di lato sul quadrato
quindi fino a che l'altro resta piu piccolo lo si aumenta finchè non incontra un mro. 
*/
void increment_delta_x_delta_y(t_ray *ray, t_c3d *c3d, double alpha)
{
    //associo il mio endpoin al primo punto di impatto.
    //aggiornerò man mano il mio end point
    ray->end_point.x = ray->first_impact_point.x;
    ray->end_point.y = ray->first_impact_point.y;
    printf("INCREMENT cardinal: %s\n", ray->cardinal_direction);
    if (strcmp(ray->cardinal_direction, "NE") == 0) //per ora ho toloto E per questinoi di testing
    {
        printf("INIZIAAAA IL CONTROLLOOOO SU NE\n");
        printf("INCREMENT ray->path_for_delta_x = %f, ray->path_for_delta_y = %f\n", fabs(ray->path_for_delta_x), fabs(ray->path_for_delta_y));
        while (1)
        {
            if (fabs(ray->path_for_delta_x) < fabs(ray->path_for_delta_y))
            {   
                printf("sez. x\n");
                //x < y
                ray->DeltaXTemp = abs(ray->delta_x) + TILE_SIZE;

                printf("INCREMENT ray->DeltaXTemp = %d\n", ray->DeltaXTemp);
                ray->SxTemporary = calculation_of_temporarySX(c3d, ray, alpha);
                               
                ray->end_point_to_check.x = c3d->player.x + fabs(ray->SxTemporary) * cos(alpha);
                ray->end_point_to_check.y = c3d->player.y + fabs(ray->SxTemporary) * sin(alpha);
               
                printf("INCREMENT ray->end_point_to_check.x = %d, ray->end_point_to_check.y = %d\n", ray->end_point_to_check.x, ray->end_point_to_check.y);
                printf("INCREMENT impact_tile: %d, %d\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
                //attenzione per far guardare al giusto quadrato ho sottratto -1 alle x quando è a NE. Non dovrebbe influire sul resto
                //inoltre attenzione questo -1 non cmbia le cooridnate di impatto ma agisce solo esternamente
                //cioè vede solo se la condizione di quella coordinata di impatto (che non varia) sottratta di uno
                //nella sua ascissa...ecc ecc...
                printf("vediamo ste coord siamo in sez x: %d, %d\n",ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);

                if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] != '1')
                {                    
                    ray->delta_x = ray->DeltaXTemp; //aggiorno il ray->delta_x che mi servirà aggiornato per l'iterazione successiva
                    ray->path_for_delta_x = ray->SxTemporary; //aggiorno per stesso motivo rigo precefente
                    ray->end_point.x = ray->end_point_to_check.x; //aggiorno il punto finale
                    ray->end_point.y = ray->end_point_to_check.y;
                    bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                    printf("print along dist_x\n");
                }
                else
                {
                     //********************** segnalibro controllo
                    t_point possible_point;
                    possible_point.x = ray->end_point.x;
                    possible_point.y = ray->end_point.y;
                    printf("sez. x: abbiamo individuato un punto di impatto. procedo a verificare se ce ne sono di precedenti\n");
                    ray->delta_x = ray->DeltaXTemp; //aggiorno il ray->delta_x che mi servirà aggiornato per l'iterazione successiva
                    ray->path_for_delta_x = ray->SxTemporary; //aggiorno per stesso motivo rigo precefente
                    //verifico se delta_x è ancora minode di delta_y
                    if (fabs(ray->path_for_delta_x) < fabs(ray->path_for_delta_y)) //AAAA possiile frizione
                    {
                        ray->end_point.x = ray->end_point_to_check.x;
                        ray->end_point.y = ray->end_point_to_check.y;
                        bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                        printf("print alond d i s t _ X\n");
                        return;
                    }
                    else
                    {
                        while(fabs(ray->path_for_delta_x) > fabs(ray->path_for_delta_y))
                        {
                            ray->DeltaYTemp = abs(ray->delta_y) + TILE_SIZE;
                            ray->SyTemporary= calculation_of_temporarySY(c3d, ray, alpha);
                            ray->end_point_to_check.x = c3d->player.x + fabs(ray->SyTemporary) * cos(alpha);
                            ray->end_point_to_check.y = c3d->player.y + fabs(ray->SyTemporary) * sin(alpha);
                       
                            //Anche qui devi aggiungere forse condizione di minore uguale
                            if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] != '1')
                            {
                                printf("ma k sfaccimm!\n");
                                ray->delta_y = ray->DeltaYTemp; //aggiorno il ray->delta_x che mi servirà aggiornato per l'iterazione successiva
                                ray->path_for_delta_y = ray->SyTemporary; //aggiorno per stesso motivo rigo precefente
                                ray->end_point.x = ray->end_point_to_check.x;
                                ray->end_point.y = ray->end_point_to_check.y;
                                bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                            }
                            else 
                            {
                                if (fabs(ray->path_for_delta_x) > fabs(ray->path_for_delta_y))
                                {
                                    ray->delta_y = ray->DeltaYTemp; //aggiorno il ray->delta_x che mi servirà aggiornato per l'iterazione successiva
                                    ray->path_for_delta_y = ray->SyTemporary; //aggiorno per stesso motivo rigo precefente
                                    ray->end_point.x = ray->end_point_to_check.x;
                                    ray->end_point.y = ray->end_point_to_check.y;
                                    bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                                    return;
                                }
                                else
                                {
                                    bresenham(c3d, c3d->player.x, c3d->player.y, possible_point.x, possible_point.y, RED);
                                    return;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                printf("Sez. Y\n");
                //sy < sx
                ray->DeltaYTemp = abs(ray->delta_y) + TILE_SIZE; ///allora da questo memoento inzia qualcosa di anomalo che cambia delta_y..non la fa aumentare di TILE_SIZE
                printf("INCREMENT ray->DeltaYTemp = %d\n", ray->DeltaYTemp);
                printf("INCREMENT ray->DeltaXTemp = %d\n", ray->DeltaXTemp);

            /*
            ############# DEBUG #########
            ok un primo problemea è che non si aggiorna path_for_delta_x quello originale.
            sembra che aumenti quello della y e quando il while ritorna da capo non entra nella condizione: 
            */


                ray->SyTemporary = calculation_of_temporarySY(c3d, ray, alpha);
                ray->end_point_to_check.x = c3d->player.x + fabs(ray->SyTemporary) * cos(alpha);
                ray->end_point_to_check.y = c3d->player.y + fabs(ray->SyTemporary) * sin(alpha);
                // printf("vediamo ste coord siamo in sez y\n");
                // printf("INCREMENT ray->end_point_to_check.x = %d, ray->end_point_to_check.y = %d\n", ray->end_point_to_check.x, ray->end_point_to_check.y);
                // printf("INCREMENT impact_tile: %d, %d\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
                if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] != '1')
                {
                    ray->delta_y = ray->DeltaYTemp; //aggiorno il ray->delta_x che mi servirà aggiornato per l'iterazione successiva
                    ray->path_for_delta_y = ray->SyTemporary; 
                    ray->end_point.x = ray->end_point_to_check.x;
                    ray->end_point.y = ray->end_point_to_check.y;
                    bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, WHITE);
                    //********************** segnalibro controllo
                    printf("ma over fai\n");
                }
                else
                {
                    //ricorda che in questo blocco sy < sx
                    t_point possible_point;
                    possible_point.x = ray->end_point.x;
                    possible_point.y = ray->end_point.y;
                    printf("sex. y: abbiamo individuato un punto di impatto. procedo a verificare se ce ne sono di precedenti\n");
                    ray->delta_y = ray->DeltaYTemp; //aggiorno il ray->delta_x che mi servirà aggiornato per l'iterazione successiva
                    ray->path_for_delta_y = ray->SyTemporary; 
                    if (fabs(ray->path_for_delta_y) < fabs(ray->path_for_delta_x))
                    {
                        ray->end_point.x = ray->end_point_to_check.x;
                        ray->end_point.y = ray->end_point_to_check.y;
                        bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, WHITE);
                        return;
                    }
                    else
                    {
                        while(fabs(ray->path_for_delta_y) > fabs(ray->path_for_delta_x)) /// AAA punto frizione
                        {
                            ray->DeltaXTemp = abs(ray->delta_x) + TILE_SIZE;
                            ray->SxTemporary = calculation_of_temporarySX(c3d, ray, alpha);
                            ray->end_point_to_check.x = c3d->player.x + fabs(ray->SyTemporary) * cos(alpha);
                            ray->end_point_to_check.y = c3d->player.y + fabs(ray->SyTemporary) * sin(alpha);
                            //anche qui metter controllo maggiore o uguale ? 
                            if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] != '1')
                            {
                                ray->delta_x = ray->DeltaXTemp; //aggiorno il ray->delta_x che mi servirà aggiornato per l'iterazione successiva
                                ray->path_for_delta_x = ray->SxTemporary; //aggiorno per stesso motivo rigo precefente
                                ray->end_point.x = ray->end_point_to_check.x;
                                ray->end_point.y = ray->end_point_to_check.y;
                                bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                            }
                            else
                            {
                                if (fabs(ray->path_for_delta_y) > fabs(ray->path_for_delta_x))
                                {
                                    ray->delta_y = ray->DeltaYTemp; //aggiorno il ray->delta_x che mi servirà aggiornato per l'iterazione successiva
                                    ray->path_for_delta_y = ray->SyTemporary; //aggiorno per stesso motivo rigo precefente
                                    ray->end_point.x = ray->end_point_to_check.x;
                                    ray->end_point.y = ray->end_point_to_check.y;
                                    bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
                                    return;
                                }
                                else
                                {
                                    bresenham(c3d, c3d->player.x, c3d->player.y, possible_point.x, possible_point.y, RED);
                                    return;
                                }
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