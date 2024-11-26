#include "c3d.h"


/*la seguente funzione:ha l'obiettivo di intercettare i colori della striscie di pixl della texture...
e riportarli sulla striscia della rappresentazione 3D.
In particolare va a prendere la corrispettiva striscia verticale su una texture.
quando hai questa strisica verticale in pratica hai i colori appuntodi quella stricia verticale.
Ebbene questi colori puoi ora usarli uno ad uno man mano che sali lungo la striscia vericale da 
disegnare nella finestra 3d.*/
static void draw_3d_wall_height_with_textute_colors(double x_3d, int x_texture, double line_heigth, t_c3d *c3d)
{
	int y_texture;
	int color;
	double max_iteration;
	double y;
	double y_min; //questa è la y_min uguale a y che serve per interpolare
	
	/*ecco risolto il segfault del while di sotto. in pratica mi sono 
	accorto che nel while con la funzione put_pixel c'era un segfault.
	la funzione in paorla determina dove andare a mettere il colore che
	gli viene passato attraverso lo scorrere del charone.
	Quindi andava in segfault perchè il char svorreva in un area di
	memoria a cui non aveva accesso. Analizzando e inserendo delle prime limitazioni
	nella condizione del while , mi sono acccorto 
	che questo comportamento anomalo scompariva se mettevo y > 0.
	Questo significa che se nel while entrava una y minore di zero allora
	andava in segfault. Ma questo significa anche che allora
	dal momento che appunto andava in segfult , allora qui
	arrivava una y che a volte aveva un valore negativo. 
	ho visto quindi quando la y può essere negativa e ho normalizzato il comportamento.
	La y può essere negativa se la line_height è maggiore della win_h.
	Pertanto se accadesse una cosa del genere...ho messo di default che la line height dovrà avere valore massimo , ovvero win_h, senza
	quindi superare la win_h stessa. Attenzione che queso controllo deve per forza
	essere fatto esternamente prima del whle..perchè prima del while
	viene impostata anche la variabile temp che va 
	a memorizzare appunto il valore in relazione alla y.*/
	if (line_heigth > c3d->win_2d.h)
		line_heigth = c3d->win_2d.h;	
	y = c3d->win_2d.w / 2 - (line_heigth / 2); /*questo centra il disegno perch+ prende la 
	
	win e la tagil a meta ...poi prnde la height, la divide a meta ...e la sottrae alla metà delo schermo
	quindi quando disegn ...una meta arriva alla meta dello schermo e l'altra proseue...essendo cosi a specchiovv*/
	y_min = y; //questa è la y_min uguale a y che serve per interpolare
	max_iteration = y + line_heigth; //questa variabile serve per l'iterazione
	while (y < max_iteration)
	{ 
		y_texture = (c3d->texture.img_dimension.heigth * ( y - y_min) ) / line_heigth; /*interpolazione*/
		color = get_pixel(&c3d->texture, x_texture, y_texture);
		put_pixel(&c3d->scene_3d, x_3d, y, color); /*AAA ora coloro nella scena_3d*/
		y_texture++;
		y++;
	}
}

/*objective: visualiza all you can see in 3D Window.
This functions wrap-up different functions IOT print one vertical line in the 3D win.*/
void draw_3d_vertical_line(t_c3d *c3d, t_point end_point, double saved_left_half_fov)
{
	int x_text;
	c3d->player.ray.projection.point = find_two_lines_intersection(c3d->player.position, c3d->player.perpendicular_direction, end_point, c3d->player.direction);
	/*##TESTING ## per vedere il collegamtno tra punto di impatto e la sua proiezione sull'asse perpendicolare alla direzione
	del giocatore...tieni scoperto il seguente bresenahm.*/
	bresenham(c3d, end_point.x, end_point.y, c3d->player.ray.projection.point.x, c3d->player.ray.projection.point.y, GREEN);
	/*##TESTING ## per vedere tutti i puntini delle proiezioni rivela il seguente draw_filled_circle*/
	draw_filled_circle(c3d,c3d->player.ray.projection.point, RADIUS/2, BLUE);
	c3d->player.ray.view3d.x_wall_line = find_x_3d(c3d->player.fov.half_left, saved_left_half_fov, c3d->raw_map.dimension.width * TILE_SIZE);
	x_text = find_x_texture(end_point, c3d->player.ray);
	c3d->player.ray.projection.length = pitagora_theorem(end_point, c3d->player.ray.projection.point);
	c3d->player.ray.view3d.height_wall_line = calculate_3d_wall_height(c3d->player.ray.projection.length);
	draw_3d_wall_height_with_textute_colors(c3d->player.ray.view3d.x_wall_line, x_text, c3d->player.ray.view3d.height_wall_line, c3d); 
}

/*itero dal confine sinistro del fov al confine destro.
cosi facendo vado a prendere di vola in volta, in ogni iterazione, 
il punto di ipatto calcolato con il dda.
questo punto di impatto lo passo (sempre nell'ambito di quella iterazione)
alla funzione visualize_3d*/
void draw_3d_fov(t_c3d *c3d)
{
	double angle_variation; /*l'ho chiamata variazione angolare!!! è una variazinoe angolare
	è la variaione angolare che di volta in volta interessa il raggio del fov che dal 
	limite sinistro va fino al limite destro...
	in pratica cosi facendo ho avviato un while che incrementa di una tot variazione angolare
	partendo dal confine sinistro del fov fino al confine destro.
	Ogi raggi oovviamente impatta su un muro...e tramite appunto il dda posso calcolare
	il punto di impatto da passare a visualize_3d*/
	t_point end_point;
	double	saved_left_half_fov; /*devo salvarmi l'half end perchè poi la faccio variare aumentandola
	fino alla parte destra del FOV*/
	point_init(&end_point);
	saved_left_half_fov = c3d->player.fov.half_left;
	angle_variation = FOV_ANGLE / NUM_OF_RAYS; /*se divido un'angolo per 10, avrò 10 
	angoli uguali più piccoli la cui somma mi da quell'angolo intero. Ora, se la mia finestra è lunga 
	500 pixel, ebbene io potrei dividere l'angolo per 500, in questo modo avrei un'iniziale corrispondenza
	di 500 angoli piccoli con 500 pixel*/
	// draw_fov_boundaries(end_point, c3d); /*approfitto per stamapare visivamente
	// i confini del fov*/
	while (c3d->player.fov.half_left < c3d->player.fov.half_right)
	{
		/*in questo while itero dal confine sinistro del fov al confine destro*/
		end_point = dda(c3d->player.position, c3d->player.fov.half_left, c3d); /*caldolo punto di impatto del raggio corrente*/
		/*## TESTING ## se vuoi vedere i raggi sparati che incontrano i muri tieni scoperto
		il seguente brehenam*/
		//bresenham(c3d, c3d->player.position.x, c3d->player.position.y, end_point.x, end_point.y, YELLOW);
		draw_3d_vertical_line(c3d, end_point, saved_left_half_fov);/*disegno la linea 3d corrispondente a quel
		punto di impatto*/
		c3d->player.fov.half_left = c3d->player.fov.half_left + angle_variation; /* aumento il raggio corrente di una variazione angolare.
		man mano la parte sinistra del fov l'aumento di un piccolo angolino.
		questo piccolo angolino l'ho calcolato prima. 
		si tratta dell'angle_variation. l'idea di fondo è che più piccolo è l'angolino 
		più riesci ad avere dettagli andando a prendere tutti gli spazi...infatti 
		è vome se fosse un fascio luminoso....
		quindi c'è un incremento minuscolo della x che va a prendere il successivo punto di impattp
		e da questo punto di impatto si va a fare il visualize 3d.*/
	}
}
