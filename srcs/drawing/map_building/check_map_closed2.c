/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closed2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:30:17 by lpennisi          #+#    #+#             */
/*   Updated: 2024/12/07 23:31:01 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

void check_previous_row(t_c3d *c3d, char **map_lines, int row_length, int prev_row_length, int i) {
    int j;

    j = row_length;
    while (j < prev_row_length) {
        if (map_lines[i - 1][j] != '1') {
            error_exit(c3d, "Error\nMap is not closed: gap in shorter row (previous row)");
        }
        j++;
    }
}

void check_next_row(t_c3d *c3d, char **map_lines, int row_length, int next_row_length, int i) {
    int j;

    j = row_length;
    while (j < next_row_length) {
        if (map_lines[i + 1][j] != '1') {
            error_exit(c3d, "Error\nMap is not closed: gap in shorter row (next row)");
        }
        j++;
    }
}

void	check_shorter_rows(t_c3d *c3d, char **map_lines, int height)
{
    int	i;
    int	row_length;
    int	prev_row_length;
    int	next_row_length;

    i = 1;
    while (i < height) {
        row_length = strlen(map_lines[i]);
        prev_row_length = strlen(map_lines[i - 1]);
        if (row_length < prev_row_length) {
            check_previous_row(c3d, map_lines, row_length, prev_row_length, i);
        }
        if (i >= height - 1)
            break;
        next_row_length = strlen(map_lines[i + 1]);
        if (row_length < next_row_length) {
            check_next_row(c3d, map_lines, row_length, next_row_length, i);
        }
        i++;
    }
}
