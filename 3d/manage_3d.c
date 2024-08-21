#include "../cub3d.h"


//this is useful to fine the intersection between
//1.: line passing through player and perpendicular to his direction
//2:: line passing for the impact_point of a ray against a wall, and parallel to player direction 
//(that is the line where the projection of that point is located)
//m1: is tan(p1_angle)  
//the linear equation of a line is: y = mx + c;
t_point find_two_lines_intersection(t_point p1, double p1_angle, t_point p2, double p2_angle) 
{
    t_point intersection;
    double c1;
    double c2;
    double m1;
    double m2;

    point_init(&intersection);
    m1 = tan(p1_angle);
    m2 = tan(p2_angle);
    c1 = p1.y - (m1 * p1.x);
    c2 = p2.y - (m2 * p2.x);
    intersection.x = (c2 - c1) / (m1 - m2);
    intersection.y = (m1 * intersection.x) + c1;
    return intersection;
}

/*  1. per ogni punto di impatto va disegnata una linea verticale sullo schermo.
    2. questa linea passa per una determinata ascissa quindi. 
    3. quel punto di impatto è associato ad un ben preciso angolo che è l'angolo del raggio associato.

Ogni raggio che parte dal giocatore rappresenta una specifica direzione 
all'interno del FOV. 
Il raggio che colpisce un punto di impatto (dopo aver percorso una certa distanza) 
determina quale colonna sullo schermo (ossia quale posizione x) sarà usata 
per disegnare quel punto di impatto come una linea verticale.

La posizione orizzontale (x della linea) sullo schermo è direttamente correlata all'angolo del raggio
rispetto alla direzione centrale di vista. 
I raggi più a sinistra (con angoli negativi rispetto alla direzione di vista) 
saranno disegnati sulla sinistra dello schermo, e quelli più a destra saranno 
disegnati sulla destra.

la proiezione indica invece l'altezza che dovrà avere quella linea colorata sullo schermo

Quindi:
io ora ho quel punto...
ho angolo di quel raggio che ha incontrao il punto
ho proiezione.
Adesso  devo fare una funzione che riceve il punto, l'angolo e la proiezione....
Questa funzione va a disegnare in una finestra una linea di pixel.
Questa linea è disegnata ad una determinata x di quella finestra che è correlata all'angolo del raggio
....e l'altezza di quella linea sarà di una certa misura correlata alla proiezione individuata

sinifica che i puntini saranno sempre equidistanti perchè i raggi sono equidistanti...
non confonderti con le proiezioni...
tu stai qui considerando le varizioni andgolai.*/

/*i raggi variano dall'estremità sinistra del fov a quella destra
un raggio centrale (bisettrice) corrisponderà a: posizione cenrale finestra
un raggio poco poco piu a sinistra corrisponde alla posizione poco poco piu a sinistra rispetto al centro della finestra...
il limite sinistro del fov coriisponde al margine della finestra.
in altri termini c'è una associazione angolare tra il fov e la width della finestra
per calcolare con quanta percentuale un angolo si trova all'interno del FOV rispetto al "margine sinistor)" */
double  find_x_3d(double ray_angle, double fov_left_ray, double win_width)
{
    double x_3d;
    double angular_fov_percentage;
    double winWidth_angle_proportion;

    angular_fov_percentage = (ray_angle - fov_left_ray) / FOV_ANGLE;
    winWidth_angle_proportion = angular_fov_percentage * win_width;
    x_3d = winWidth_angle_proportion;
    //mlx_pixel_put(c3d->win_2d.mlx_connection, c3d->win_3d.mlx_win, x_3d, 250, WHITE); //for 3d win
    return (x_3d);
}

double wall_heigth_3d(double projection)
{
	double line_height;

	line_height = SCALE_FACTOR / projection;
	return (line_height);
}

void draw_line_heigths(double x_3d, double line_heigth, t_c3d *c3d)
{
	double y;
	y = c3d->win_2d.w / 2 - (line_heigth / 2);
    double tmp = y + line_heigth;
	while (y < tmp)
	{

    	mlx_pixel_put(c3d->win_2d.mlx_connection, c3d->win_3d.mlx_win, x_3d, y, RED); //for 3d win
		y++;
	}
}

double pitagora_theorem(t_point first_point, t_point second_point)
{
	double result;
	double dx;
	double dy;

	dx = first_point.x - second_point.x;
	dy = first_point.y - second_point.y;
	result = sqrt(pow(dx, 2) + pow(dy, 2));
	return (result);
}





