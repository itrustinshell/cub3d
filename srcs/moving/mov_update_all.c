#include "c3d.h"

/*questa funzione è chiamata da loop_hook nel main
e resta in ascolto continuamente sulle proprietà
del player move_up, move_right_move_left ecc..
Se ueste proprietà sono settate a 1 da qaualche parte allora la funzione aggiorna le 
coordinate del player.
Tale settaggio avviene in key_press e key_release*/
int update_movement(void *param)
{
	int pos_updated;
	int rot_updated;

	pos_updated = update_position(param);
	rot_updated = update_alpha_rotation(param);
	if (pos_updated || rot_updated)
		drawing_routine((t_c3d *)param);
	return (0);
}
