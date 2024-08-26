#include "../cub3d.h"



/*questa funzione è inutilizzata...serve per scopi di testing.
se vuoi usarla la inserisci al posto di draw_3d_wall_height_with_textute_colors.
quindi va inserita nell'ambito di visualize_3d.
In ogni caso questa funione ha lo scopo di disegnare le linee verticali nella mappa 3d.
ma adifferenza dell'altra funzione, non va a prendere i colori dalla texture, bensi 
più semplicemente colora ogni cosa di un solo colore, ad esempio
il colore rosso. Tutte le altezze disegnate nella mappa 3d quindi avrebbero 
un solo colore.*/
// static void draw_3d_wall_height_with_one_color(double x_3d, double line_heigth, t_c3d *c3d)
// {
// 	double y;
// 	y = c3d->win_2d.w / 2 - (line_heigth / 2);
//     double tmp = y + line_heigth;
// 	while (y < tmp)
// 	{

//     	mlx_pixel_put(c3d->mlx_connection, c3d->win_3d.mlx_win, x_3d, y, RED); //for 3d win
// 		y++;
// 	}
// }

/*la seguente funzione:ha l'obiettivo di intercettare i colori della striscie di pixl della texture...
e riportarli sulla striscia della rappresentazione 3D.
In particolare va a prendere la corrispettiva striscia verticale su una texture.
quando hai questa strisica verticale in pratica hai i colori appuntodi quella stricia verticale.
Ebbene questi colori puoi ora usarli uno ad uno man mano che sali lungo la striscia vericale da 
disegnare nella finestra 3d.*/
static void draw_3d_wall_height_with_textute_colors(double x_3d, int x_texture, double line_heigth, t_c3d *c3d)
{
	int y_texture;
	int ciao;
	ciao = x_texture;
	double y;

	y_texture = 0;
	y = c3d->win_2d.w / 2 - (line_heigth / 2);
    double tmp = y + line_heigth;
	int color;
	color = RED;
	int u;
	u = color;
	while (y < tmp)
	{
		// printf("weeeeee x_Textur:%d\n", x_texture);
		 color = get_pixel(&c3d->texture, x_texture, y_texture);
		//printf("vir si mo cagn il colore:%d\n", color);
    	mlx_pixel_put(c3d->mlx_connection, c3d->win_3d.mlx_win, x_3d, y, color); //for 3d win
		 y_texture++;
		y++;
	}
}

/*
objective: visualiza all you can see in 3D Window.
This functions wrap-up different functions IOT print one vertical line in the 3D win.
*/
void draw_3d_visualization(t_c3d *c3d, t_point end_point, double saved_left_half_fov)
{
	int x_text;
	c3d->player.ray.projection.point = find_two_lines_intersection(c3d->player.position, c3d->player.perpendicular_direction, end_point, c3d->player.direction);
	c3d->player.ray.view3d.x_wall_line = find_x_3d(c3d->player.fov.half_left, saved_left_half_fov, c3d->raw_map.dimension.width * TILE_SIZE);
	x_text = find_x_texture(end_point);
	c3d->player.ray.projection.length = pitagora_theorem(end_point, c3d->player.ray.projection.point);
	c3d->player.ray.view3d.height_wall_line = calculate_3d_wall_height(c3d->player.ray.projection.length);
	draw_3d_wall_height_with_textute_colors(c3d->player.ray.view3d.x_wall_line, x_text, c3d->player.ray.view3d.height_wall_line,  c3d);
}

/*itero dal confine sinistro del fov al confine destro.
cosi facendo vado a prendere di vola in volta, in ogni iterazione, 
il punto di ipatto calcolato con il dda.
questo punto di impatto lo passo (sempre nell'ambito di quella iterazione)
alla funzione visualize_3d*/
void draw_field_of_view(t_c3d *c3d)
{
	double angle_variation; /*l'ho chiamata variazione angolare!!! è una variazinoe angolare
	è la variaione angolare che di volta in volta interessa il raggio del fov che dal 
	limite sinistro va fino al liminte destro...
	in pratica cosi facendo ho avviato un while che incrementa di una tot variazione angolare
	partendo dal confine sinistro del fov fino al confine destro.
	Ogi raggi oovviamente impatta su un muro...e tramite appunto il dda posso calcolare
	il punto di impatto da passare a visualize_3d*/
	t_point end_point;
	double	saved_left_half_fov; /*devo salvarmi l'half end perchè poi la faccio variare aumentandola
	fino alla parte destra del FOV*/

	saved_left_half_fov = c3d->player.fov.half_left;
	angle_variation = FOV_ANGLE / c3d->win_3d.w; /*se divido un'angolo per 10, avrò 10 
	angoli uguali più piccoli la cui somma mi da quell'angolo intero. Ora, se la mia finestra è lunga 
	500 pixel, ebbene io potrei dividere l'angolo per 500, in questo modo avrei un'iniziale corrispondenza
	di 500 angoli piccoli con 500 pixel*/
	point_init(&end_point);
	// draw_fov_boundaries(end_point, c3d); /*approfitto per stamapare visivamente
	// i confini del fov*/
	while (c3d->player.fov.half_left < c3d->player.fov.half_right)
	{
		/*in questo while itero dal confine sinistro del fov al confine destro*/
		end_point = dda(c3d->player.position, c3d->player.fov.half_left, c3d); /*caldolo punto di impatto del raggio corrente*/
		draw_3d_visualization(c3d, end_point, saved_left_half_fov); /*passo il punto di impatto a visualize 3d---e vedi cosa fa visualize 3d*/
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
