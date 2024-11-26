#include "c3d.h"

/*this function set texture utilizing minilibx functions*/
void	set_texture(t_img *texture, void *mlx_connection)
{
    /*a differenza delle funzioni di mlx che agiscono sulle immagini,
    quelle che agiscono sulle texture impostano in automatico
    le dimensioni delle immagini (ovvero delle immagini
    che saranno associate alle texture. 
    Questo significa che non dovrai impostare tu le dimensioni.*/
	texture->img = mlx_xpm_file_to_image(mlx_connection, PATH_TO_TEXTURE, &texture->img_dimension.width, &texture->img_dimension.heigth);
    texture->data_addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->size_line, &texture->endian);
}
