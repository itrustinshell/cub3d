#include "../cub3d.h"
#include <string.h>

/*this function is an easy way to find the direction the player is looking at. 
this is useful to determin the coordinate of the CELL where he should looking at.
for example if he look at 45°, and he is in the cell 3,2
is possible that he will encounter something toword right and or up
*/
int get_cardinal_direction(double angle)
{
	int	cardinal_direction;
	cardinal_direction = 0;

	if (angle == 0 || angle == 2 * M_PI)
		cardinal_direction = E;
	else if (angle == M_PI)    
		cardinal_direction = W;
	else if (angle == M_PI / 2)    
		cardinal_direction = S;
	else if (angle > 0  && angle < M_PI / 2)
		cardinal_direction = SE;
	else if (angle >  M_PI / 2  && angle < M_PI)
		cardinal_direction = SW;
	else if (angle > M_PI && angle < ((3 * M_PI) / 2))
		cardinal_direction = NW;
	else if (angle > ((3 * M_PI) / 2)  && angle < 2 * M_PI)
		cardinal_direction = NE;
	else if (angle == (3 * M_PI) / 2)
		cardinal_direction = N;
	printf("you are looking at %d\n", cardinal_direction);
	return (cardinal_direction);
}

/*this function chose the side of the tile, and consequently the point 
according to angle_direction. This is useful to get the later the distance
dx and dy from that side.
*/
t_point chose_side_point(t_point first_point, int cardinal_direction)
{
	t_point tile_ref;
	tile_ref.x = 0;
	tile_ref.y = 0;

	t_point side_point;
	side_point.x = 0;
	side_point.y = 0;

	tile_ref = tile_reference(first_point);

	if (cardinal_direction == NE  || cardinal_direction == E)
	{
		side_point.x = ((int)tile_ref.x + 1) * TILE_SIZE;
		side_point.y = (int)tile_ref.y * TILE_SIZE;
	}
	else if (cardinal_direction == NW || cardinal_direction == W || cardinal_direction == N)
	{
		side_point.x = (int)tile_ref.x * TILE_SIZE;
		side_point.y = (int)tile_ref.y * TILE_SIZE;
	}
	else if (cardinal_direction == SE)
	{
		side_point.x = ((int)tile_ref.x + 1) * TILE_SIZE;
		side_point.y = ((int)tile_ref.y + 1) * TILE_SIZE;
	}
	else if (cardinal_direction == SW || cardinal_direction == S)
	{
		side_point.x = (int)tile_ref.x * TILE_SIZE;
		side_point.y = ((int)tile_ref.y + 1) * TILE_SIZE;
	}
	return (side_point);
}

t_point reaching_first_side(char **map_grid, double alpha, t_c3d *c3d, t_ray *ray) //la verisone commentata è nel file versioni
{   
	t_point first_impact_point_along_pathX; //calcolo sia il punto con sx che con sy
	t_point first_impact_point_along_pathY;
	ray->first_side_point = chose_side_point(c3d->player.position, ray->cardinal_direction); //individua uno dei vertici interni della cella
	
	ray->delta = calculate_delta(c3d->player.position, ray->first_side_point, ray->cardinal_direction); printf("\nla prima cella verso cui il raggio si sta dirigendo è: %d, %d\n", (int)ray->first_side_point.x / TILE_SIZE,  (int)ray->first_side_point.y /TILE_SIZE); printf("ray.delta.x = %f, ray.delta.y = %f\n", fabs(ray->delta.x), fabs(ray->delta.y));  //#NOTA_1
	ray->path = calculate_path(ray->delta, alpha);
	first_impact_point_along_pathX = trigonometric_pointCalculation(c3d->player.position,ray->path.x, alpha);/*calcolo il punto lungo sx */ printf("primo punto calcolato con path_x: %d, %d\n", (int)first_impact_point_along_pathX.x, (int)first_impact_point_along_pathX.y);
	first_impact_point_along_pathY = trigonometric_pointCalculation(c3d->player.position,ray->path.y, alpha); printf("primo punto calcolato con path_y: %d, %d\n", (int)first_impact_point_along_pathY.x, (int)first_impact_point_along_pathY.y);
	
	if (!is_it_inside_map_perimeter(first_impact_point_along_pathX, c3d)) //#NOTA_2 
		return (first_impact_point_along_pathY);
	else if (is_it_a_wall(first_impact_point_along_pathX, c3d->map_fm_file.grid))
		return (check_if_are_both_walls_and_set_firstSidePoint(first_impact_point_along_pathX, first_impact_point_along_pathY, map_grid, ray, c3d));
	else
	{
		if (!is_it_inside_map_perimeter(first_impact_point_along_pathY, c3d)) //# NOTA_2
			return (first_impact_point_along_pathX);
		if (is_it_a_wall(first_impact_point_along_pathY, c3d->map_fm_file.grid)) //il punto su sx non era di un muro, quindi ha skippato qulla parte...allora vediamo se us sy il punto è di un muro
			return(first_impact_point_along_pathY);			//qui significa che il punto con sx non appartiene ad un muro, ma quello con sy si! quindi ritorna il punto ottenuto con sx
		else //per esssere a questo punto significa che nessuno dei precedenti punti appartiene ad un muro quindi riestituisci sempricemente il punto appartemente all'ipotenusa piu corta
		{
			if (fabs(ray->path.x) <= fabs(ray->path.y)) //confronto tra ipotenuse
				return (first_impact_point_along_pathX);
			else
				return (first_impact_point_along_pathY);
		}
	} printf("punto di impatto: %d, %d\n",(int)ray->first_impact_point.x, (int)ray->first_impact_point.y);
	return (first_impact_point_along_pathY);

}


	/* # NOTA_1
	I Verify what is the shorter distance (I use fabs to avoid negatives)
	I return the end-point of the shortest distance.
	*/
   //mi serve trovare ogni volta l'ipotenusa perchè graie a quella mi calcolo il cpunto di impatto con cos e sen
   //ora quando effettuo il raggiungimento del primo punto di impatto, per la prima volta viene calcolato sx e dx.
   /*
   successivamente viene scelto il segmento con lunghezza minore e quindi si restituisce la coordinata del punto di impatto.
   Poniamo il caso che il segmento minore fosse stato sx.
   ma poniamo anche il caso che sy (che non viene preso quindi in considerazion eprchè più lungo) impattaca contro un muro.
   Ebbene questa infromazione potrebbe essere persa.
   Infatti a seguire dalla prima individuazione del primo punto di impatto (che qui abbiamo detto essere indiciduadto con sx),
   gli incrementi successivi sono fatti di TILE_SIZE in TILE_SIZE e pertanto si perderebbe che nel primo sy il raggio aveva impattato
   contro il muro.
   Pertanto conviene a prescindere calcolare i due punti di impatto, un con sx e uno con sy, per essere sicuri che nessuno dei due abbia impattato su un muro.
   solo dopo fare la differenza tra i due per verificare qualce effettivamente è il più piccolo (ovvero quale dei due è anche il primo punto di impatto).
   Essendo la prima volta che un punto incontro solo e soltanto due bene precisi assi allora dovrai ritornare il punto piu piccolo se entrambi sono
   punti di impatto su un muro.... appure ritorni solo il punto piu grande se è un punto di impatto su un muro.
   altrimenti ritorni solo il numero piu piccolo (ovvero quando nessuno dei due è un punto di impatto su un muro)
   */

  	/* #NOTA_2
		inizio con il punto calcolato su sx. Farò lo stesso dopo con sy. 
		In pratica voglio sapere se questo punto è già oltre i confini del mio permimetro.
		per perimetro intendiamo proprio l'aria interna, quella che va oltre il punto di impatto interno.
		Per intenderci intorno alla mappa verrà a crearsi un perimetro.
		Ogni cella di questo perimetro è un quadrato.
		prendnendo un punto che viaggia verso NE questo potrebbe incontrare quel quadrato su suo lato sinistro.
		Ecco cosa intendo per perimetro. Quel lato sinistro è il limite.
		Quindi quand'anche un punto cadesse all'interno di una cella del perimetro ma oltrepassasse tale limite interno,
		ebbene sarebbe al di fuori del perimetro cosi come definito.
		Ora proseguento: se una punto cade fuori questo perimetro significa che matematicamente quel punto ha il corrispetticvo 
		sx (o sx) maggiore dell'altro puto calcolato lungo sy (o sx).
		Quindi dovrò restituire matematicamente l'altro punto. E la funzione non prosegue...ecco perchè c'è un return.
		Se poi il punto tornato è lungo (ma non oltre) il confine, oppure è un muro interno, verrà gestito in dda 
		che non passa la plla a increment qualora ppunto appartenesse ad un muro, altrimenti se non fosse un muro,
		passerebbe la palla a incrment che andrebbe a calcolare il punto di impatto per i successivi incrementi.
		*/