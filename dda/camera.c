#include "../cub3d.h"

//attenzione che qui i punti sono costruiti non in funzione dellap osizione del player ma della camera
t_camera camera_plane(t_point player_position, double player_direction, t_c3d *c3d)
{
    t_camera    camera;

    camera.fov_rigth_point.x = player_position.x + (CAMERA_DISTANCE * cos(player_direction + FOV / 2));
    camera.fov_rigth_point.y  = player_position.y + (CAMERA_DISTANCE * sin(player_direction + FOV / 2));
 	draw_filled_circle(c3d, camera.fov_rigth_point, RADIUS / 2, BLACK);
    
    camera.fov_left_point.x = player_position.x + (CAMERA_DISTANCE * cos(player_direction - FOV / 2));
    camera.fov_left_point.y = player_position.y + (CAMERA_DISTANCE * sin(player_direction - FOV / 2));


    draw_filled_circle(c3d, camera.fov_left_point, RADIUS / 2, BLACK);
    bresenham(c3d, (int)camera.fov_left_point.x, (int)camera.fov_left_point.y, (int)camera.fov_rigth_point.x, (int)camera.fov_rigth_point.y, BLACK);

    bresenham(c3d, (int)player_position.x, (int)player_position.y, (int)camera.fov_rigth_point.x, (int)camera.fov_rigth_point.y, BLACK);
    bresenham(c3d, (int)camera.fov_left_point.x, (int)camera.fov_left_point.y, (int)player_position.x, (int)player_position.y, BLACK);

return camera;
///AAA qui si inverte addizione e sottrazione per calclare gli angolo perchè i triangoloi rettangolison capovolti quinid si va a prendere il seno dall'altro lato e il cosedno anche
}

