/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:18:50 by lpennisi          #+#    #+#             */
/*   Updated: 2025/03/15 16:54:18 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"
static int	check_ne(char **map_grid, double card_dir, t_point point_to_verify)
{
    t_point	p;
    int		px;
    int		py;
    int		map_height;
    int		map_width;

    p.x = 0;
    p.y = 0;
    p = point_to_verify;
    px = (int)p.x;
    py = (int)p.y;
    map_height = ft_strlen(map_grid[0]);
    map_width = ft_arrlen(map_grid);
    if (card_dir == NE)
    {
        if (py / TILE_SIZE >= map_width || (px - 1) / TILE_SIZE >= map_height || (py + 1) / TILE_SIZE >= map_width || px / TILE_SIZE >= map_height)
            return (ft_printf("HELLLLOOOOO\n"), FALSE);
        if (map_grid[py / TILE_SIZE][(px - 1) / TILE_SIZE] == '1' && \
        map_grid[(py + 1) / TILE_SIZE][px / TILE_SIZE] == '1')
        {
            p.x = p.x - 1;
            p.y = p.y + 1;
            return (TRUE);
        }
    }
    return (FALSE);
}

static int	check_nw(char **map_grid, double card_dir, t_point point_to_verify)
{
    t_point	p;
    int		px;
    int		py;
    int		map_height;
    int		map_width;

    p.x = 0;
    p.y = 0;
    p = point_to_verify;
    px = (int)p.x;
    py = (int)p.y;
    map_height = ft_strlen(map_grid[0]);
    map_width = ft_arrlen(map_grid);
    if (card_dir == NW)
    {
        if (py / TILE_SIZE >= map_width || (px + 1) / TILE_SIZE >= map_height || (py + 1) / TILE_SIZE >= map_width || px / TILE_SIZE >= map_height)
            return (ft_printf("HELLLLOOOOO\n"), FALSE);
        if (map_grid[py / TILE_SIZE][(px + 1) / TILE_SIZE] == '1' && \
        map_grid[(py + 1) / TILE_SIZE][px / TILE_SIZE] == '1')
        {
            p.x = p.x - 1;
            p.y = p.y + 1;
            return (TRUE);
        }
    }
    return (FALSE);
}

static int	check_se(char **map_grid, double card_dir, t_point point_to_verify)
{
    t_point	p;
    int		px;
    int		py;
    int		map_height;
    int		map_width;

    p.x = 0;
    p.y = 0;
    p = point_to_verify;
    px = (int)p.x;
    py = (int)p.y;
    map_height = ft_strlen(map_grid[0]);
    map_width = ft_arrlen(map_grid);
    if (card_dir == SE)
    {
        if (py / TILE_SIZE >= map_width || (px - 1) / TILE_SIZE >= map_height || (py - 1) / TILE_SIZE >= map_width || px / TILE_SIZE >= map_height)
            return (ft_printf("HELLLLOOOOO\n"), FALSE);
        if (map_grid[py / TILE_SIZE][(px - 1) / TILE_SIZE] == '1' && \
        map_grid[(py - 1) / TILE_SIZE][px / TILE_SIZE] == '1')
        {
            p.x = p.x - 1;
            p.y = p.y + 1;
            return (TRUE);
        }
    }
    return (FALSE);
}

static int	check_sw(char **map_grid, double card_dir, t_point point_to_verify)
{
    t_point	p;
    int		px;
    int		py;
    int		map_height;
    int		map_width;

    p.x = 0;
    p.y = 0;
    p = point_to_verify;
    px = (int)p.x;
    py = (int)p.y;
    map_height = ft_strlen(map_grid[0]);
    map_width = ft_arrlen(map_grid);
    if (card_dir == SW)
    {
        if (py / TILE_SIZE >= map_width || (px + 1) / TILE_SIZE >= map_height || (py - 1) / TILE_SIZE >= map_width || px / TILE_SIZE >= map_height)
            return (ft_printf("HEAAAAAAOOO\n"), FALSE);
        if (map_grid[py / TILE_SIZE][(px + 1) / TILE_SIZE] == '1' && \
        map_grid[(py - 1) / TILE_SIZE][px / TILE_SIZE] == '1')
        {
            p.x = p.x - 1;
            p.y = p.y + 1;
            return (TRUE);
        }
    }
    return (FALSE);
}
int	is_it_passing_between_two_walls(t_ray *ray, char **map_grid, t_point p)
{
	double	direction;

	direction = ray->cardinal_direction;
	if (check_ne(map_grid, direction, p))
		return (TRUE);
	else if (check_se(map_grid, direction, p))
		return (TRUE);
	else if (check_nw(map_grid, direction, p))
		return (TRUE);
	else if (check_sw(map_grid, direction, p))
		return (TRUE);
	return (FALSE);
}
