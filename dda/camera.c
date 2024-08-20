#include "../cub3d.h"

//attenzione che qui i punti sono costruiti non in funzione dellap osizione del player ma della camera

//a questo livello funzionano le normali operazioni ancohe on numeri negativi non avendo normalizzato nulal...ma perchè non sono necerssarie
//qui non normalizzo gli angoli .....gli angoli sono non normalizzati...si muovnon anche oltre il 2 pigreco ma
//cmq non eccedono certi limiti perchè  se provi a vdere le stampe poco dopo ritornano a capo
//ma questo perchè sono calcolati ripsetto ad un angolo del giocatore che si quelo è sempre normalizzato
//quindi siccome il fov è cmq minore dell'alngolo giro e non sarà mai superiore per costruzione e definizione di una vista di un umano
//potrebbe andar beena nche cosi la festione....tanto gli angoli negativi anche con lo zero sono considerati appunto come corrispottivi molto grandi
//ogni angolo è al suo posto e viene tutto gestito adeguatamente.
//Ecco perchè funziona....
//cmq ricorda che la direzione alpfha del giocatore resta normalizzata
//quindi significa che quando ripoarti da zero dopo una rotazione completa cmq quella direzione riparte da zero o 2pigreco
//questo è importante perchè è da questa che sono sottratti i fov/2
t_camera camera_plane(t_point player_position, double player_direction, t_c3d *c3d)
{
    t_camera    camera;

    camera.fov_rigth_point.x = player_position.x + (CAMERA_DISTANCE * cos(player_direction + FOV_ANGLE / 2));
    camera.fov_rigth_point.y  = player_position.y + (CAMERA_DISTANCE * sin(player_direction + FOV_ANGLE / 2));
 	draw_filled_circle(c3d, camera.fov_rigth_point, RADIUS / 2, GREEN);
    
    camera.fov_left_point.x = player_position.x + (CAMERA_DISTANCE * cos(player_direction - FOV_ANGLE / 2));
    camera.fov_left_point.y = player_position.y + (CAMERA_DISTANCE * sin(player_direction - FOV_ANGLE / 2));


    draw_filled_circle(c3d, camera.fov_left_point, RADIUS / 2, RED);
    bresenham(c3d, (int)camera.fov_left_point.x, (int)camera.fov_left_point.y, (int)camera.fov_rigth_point.x, (int)camera.fov_rigth_point.y, BLACK);

    bresenham(c3d, (int)player_position.x, (int)player_position.y, (int)camera.fov_rigth_point.x, (int)camera.fov_rigth_point.y, BLACK);
    bresenham(c3d, (int)camera.fov_left_point.x, (int)camera.fov_left_point.y, (int)player_position.x, (int)player_position.y, BLACK);

printf("\n\ncameraaaaaaaaaaaaaa\n");
printf("angolo del giocatore: %f\n", player_direction);
printf("angolo fov: %f\n", FOV_ANGLE);
printf("rigth: angolo giocatore + FOV_ANGLE/2: %f\n", player_direction + FOV_ANGLE / 2);
printf("left: angolo giocatore - FOV_ANGLE/2: %f\n", player_direction - FOV_ANGLE / 2);


return camera;
///AAA qui si inverte addizione e sottrazione per calclare gli angolo perchè i triangoloi rettangolison capovolti quinid si va a prendere il seno dall'altro lato e il cosedno anche
}

// double projection()
// {
//     double projection;
//     return (projection);

// }