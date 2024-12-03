/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:55:11 by lpennisi          #+#    #+#             */
/*   Updated: 2024/12/03 18:32:42 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int	check_texture_path(t_map *raw_map, char *line) {
	char *path;
	char *ptr;

	ptr = ft_strchr(line, ' ');
	if (!ptr)
		return (2);
	path = ft_strdup(ptr + 1);
	if (ft_strncmp(line, "NO ", 3) == 0)
		raw_map->NO_texture = path;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		raw_map->SO_texture = path;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		raw_map->WE_texture = path;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		raw_map->EA_texture = path;
	else
		return (free(path), 2);
	if (access(path, F_OK) == -1)
		return (1);
	return (0);
}

int	check_color_format(t_map *raw_map, char *line) {
	int		r;
	int		g;
	int		b;
	char	**splitted;
	char	*color;

    if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0) {
        color = ft_strchr(line, ' ') + 1;

		splitted = ft_split(color, ',');
		if (ft_arrlen(splitted) == 3)
		{
			r = ft_atoi(splitted[0]);
			g = ft_atoi(splitted[1]);
			b = ft_atoi(splitted[2]);
			if (!(r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255))
			{
				if (ft_strncmp(line, "F ", 2) == 0)
					raw_map->F_color = ft_strdup(color);
				else
					raw_map->C_color = ft_strdup(color);
				return (ft_free_matrix(splitted, -1), 0);
			}
		}
		return (ft_free_matrix(splitted, -1), 1);
    }
	return (2);
}

int	is_map_character(char c) {
	if (c == '0' || c == '1' || c == 'N' \
	|| c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_player_character(char c) {
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	get_orientation(char c) {
	if (c == 'N')
		return (N);
	else if (c == 'S')
		return (S);
	else if (c == 'E')
		return (E);
	else if (c == 'W')
		return (W);
}

int	check_map_characters(t_map *raw_map, char **lines) {
	int	i;
	int	j;

	i = -1;
	while (lines[++i])
	{
		j = -1;
		while (lines[i][++j])
		{
			if (!is_map_character(lines[i][j]))
				return (1);
			else if (is_player_character(lines[i][j]))
				if (!raw_map->player_orientation)
				{
					raw_map->player_position = (t_point){j * TILE_SIZE + TILE_SIZE/2, i * TILE_SIZE + TILE_SIZE/2};
					raw_map->player_orientation = get_orientation(lines[i][j]);
				}
				else
					return (1);
		}
	}
	if (!raw_map->player_orientation)
		return (1);
	return (0);
}

void check_map_closed(t_c3d *c3d, char **map_lines) {
    int i, j;
    int height;

    height = ft_arrlen(map_lines);
	c3d->raw_map.dimension.h = height;
    // Controlla la prima e l'ultima riga
    for (j = 0; map_lines[0][j]; j++) {
        if (map_lines[0][j] != '1' && map_lines[0][j] != ' ' && map_lines[0][j] != '\t') {
            error_exit(c3d, "Error\nMap is not closed: first row");
        }
    }
    for (j = 0; map_lines[height - 1][j]; j++) {
        if (map_lines[height - 1][j] != '1' && map_lines[height - 1][j] != ' ' && map_lines[height - 1][j] != '\t') {
            error_exit(c3d, "Error\nMap is not closed: last row");
        }
    }

    // Controlla la prima e l'ultima colonna di ogni riga
    for (i = 0; i < height; i++) {
        int row_length = strlen(map_lines[i]);
		if (c3d->raw_map.dimension.w < row_length)
			c3d->raw_map.dimension.w = row_length;
        // Controlla la prima colonna
        if (map_lines[i][0] != '1' && map_lines[i][0] != ' ' && map_lines[i][0] != '\t') {
            error_exit(c3d, "Error\nMap is not closed: first column");
        }

        // Controlla l'ultima colonna
        if (map_lines[i][row_length - 1] != '1' && map_lines[i][row_length - 1] != ' ' && map_lines[i][row_length - 1] != '\t') {
            error_exit(c3d, "Error\nMap is not closed: last column");
        }

        for (j = 1; j < row_length - 1; j++) {
            if (map_lines[i][j] == ' ') {
                if ((i > 0 && map_lines[i - 1][j] == '0') || 
                    (i < height - 1 && map_lines[i + 1][j] == '0') || 
                    (j > 0 && map_lines[i][j - 1] == '0') || 
                    (j < row_length - 1 && map_lines[i][j + 1] == '0')) {
                    error_exit(c3d, "Error\nMap is not closed: space inside row adjacent to '0'");
                }
            }
        }
    }

    // Controlla che le righe più corte siano chiuse correttamente
    for (i = 1; i < height; i++) {
        int row_length;
        int prev_row_length;
        int next_row_length;
	
		row_length = strlen(map_lines[i]);
		prev_row_length = strlen(map_lines[i - 1]);
        // Caso in cui la riga è più corta della riga precedente
        if (row_length < prev_row_length) {
            for (j = row_length; j < prev_row_length; j++) {
                if (map_lines[i - 1][j] != '1') {
                    error_exit(c3d, "Error\nMap is not closed: gap in shorter row (previous row)");
                }
            }
        }
		if (i >= height - 1)
			break;
		next_row_length = strlen(map_lines[i + 1]);
        // Caso in cui la riga è più corta della riga successiva
        if (row_length < next_row_length) {
            for (j = row_length; j < next_row_length; j++) {
                if (map_lines[i + 1][j] != '1') {
                    error_exit(c3d, "Error\nMap is not closed: gap in shorter row (next row)");
                }
            }
        }
    }
}

void	remove_consecutives_space(char **lines)
{
	int i;
	int j;
	int k;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == ' ' && lines[i][j + 1] == ' ')
			{
				k = j;
				while (lines[i][k])
				{
					lines[i][k] = lines[i][k + 1];
					k++;
				}
				lines[i][k] = '\0';
			}
			j++;
		}
		i++;
	}
}

void	remove_extra_space(char **lines)
{
	int i;
	int j;
	int k;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] == ' ')
			j++;
		if (j > 0)
		{
			k = 0;
			while (lines[i][j + k])
			{
				lines[i][k] = lines[i][j + k];
				k++;
			}
			lines[i][k] = '\0';
		}
		i++;
	}
	remove_consecutives_space(lines);
}

int	are_information_set(t_map raw_map) {
	if (!raw_map.NO_texture || !raw_map.SO_texture || !raw_map.WE_texture \
	|| !raw_map.EA_texture || !raw_map.F_color || !raw_map.C_color)
		return (0);
	return (1);
}

void	check_texture_data(t_c3d *c3d) {
	t_map *raw_map;
	char **lines;
	int status;
	int status2;
	int i;

	raw_map = &c3d->raw_map;
	lines = ft_split(raw_map->texture_data, '\n');
	i = -1;
	remove_extra_space(lines);
    while (lines[++i])
	{
		status = check_texture_path(raw_map, lines[i]);
       	if (status == 1)
			error_exit(c3d, INVALID_TEXTURE_PATH);
        status2 = check_color_format(raw_map, lines[i]);
		if (status2 == 1)
			error_exit(c3d, INVALID_COLOR_FORMAT);
		if (status2 == 2 && status == 2)
			error_exit(c3d, INVALID_MAP);
    }
	if (!are_information_set(*raw_map))
		error_exit(c3d, MISSING_INFORMATION);
	ft_free_matrix(lines, -1);
}

void parse_and_check(t_c3d *c3d) {
	t_map *raw_map;
	char **map_lines;
    int i;

	check_texture_data(c3d);
	raw_map = &c3d->raw_map;
	map_lines = ft_split(raw_map->map_data, '\n');
	if (check_map_characters(raw_map, map_lines))
		error_exit(c3d, INVALID_CHARACTER);
	c3d->player.position = raw_map->player_position;
	c3d->player.tile = tile_reference(c3d->player.position);
	set_player_orientation(c3d);
    check_map_closed(c3d, map_lines);
	c3d->raw_map.grid = map_lines;
}