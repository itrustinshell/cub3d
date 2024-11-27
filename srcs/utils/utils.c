/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:34:10 by lpennisi          #+#    #+#             */
/*   Updated: 2024/11/27 12:31:08 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

/*this function set texture utilizing minilibx functions*/
void	set_texture(t_img *texture, void *mlx_connection)
{
    /*a differenza delle funzioni di mlx che agiscono sulle immagini,
    quelle che agiscono sulle texture impostano in automatico
    le dimensioni delle immagini (ovvero delle immagini
    che saranno associate alle texture. 
    Questo significa che non dovrai impostare tu le dimensioni.*/
	texture->img = mlx_xpm_file_to_image(mlx_connection, PATH_TO_TEXTURE, &texture->img_dimension.w, &texture->img_dimension.h);
    texture->data_addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->size_line, &texture->endian);
}

static void set_win_dimensions(t_win *win_2d, t_win *win_3d, t_dimension map_fm_file_dimension)
{
win_2d->dimension.w = TILE_SIZE * map_fm_file_dimension.w;	//TODO: Substitute with ft_atoi from libft
win_2d->dimension.h = TILE_SIZE * map_fm_file_dimension.h;
win_3d->dimension.w = TILE_SIZE * map_fm_file_dimension.w;
win_3d->dimension.h = TILE_SIZE * map_fm_file_dimension.h;;
}

void set_connection_and_windows(t_c3d *c3d)
{
	set_win_dimensions(&c3d->win_2d, &c3d->win_3d, c3d->raw_map.dimension);
    c3d->mlx_connection = mlx_init();
    c3d->win_2d.mlx_win = mlx_new_window(c3d->mlx_connection, c3d->win_2d.dimension.w, c3d->win_2d.dimension.h, "cub3d_2d");
	c3d->win_3d.mlx_win = mlx_new_window(c3d->mlx_connection, c3d->win_3d.dimension.w, c3d->win_3d.dimension.h, "cub3d_3d");
}
