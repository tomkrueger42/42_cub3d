/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:10:16 by tkruger           #+#    #+#             */
/*   Updated: 2022/06/19 17:10:17 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>

int	valid_line(char *line);

char	*find_map(char *lines)
{
	char	*map_start;

	while (*lines != '\0' && valid_line(lines) == 0)
	{
		if (ft_strchr(lines, '\n') == 0)
			return (NULL);
		lines = ft_strchr(lines, '\n') + 1;
	}
	map_start = lines;
	while (*lines != '\0')
	{
		if (valid_line(lines) == 0 && *lines != '\n')
			put_error_and_exit("invalid map");
		if (ft_strchr(lines, '\n'))
			lines = ft_strchr(lines, '\n') + 1;
		else
			break ;
	}
	if (map_start == lines)
		return (NULL);
	return (map_start);
}

int	valid_line(char *line)
{
	size_t	index;

	index = 0;
	while (line[index] != '\0' && line[index] != '\n')
	{
		if (ft_strchr(MAP_CHARS, line[index]))
			index++;
		else
			return (0);
	}
	return (index);
}

void	count_dimensions(char **data)
{
	int	y;

	y = 0;
	while (data != NULL && data[y] != NULL)
	{
		if (get_map()->width < ft_strlen(data[y]))
			get_map()->width = ft_strlen(data[y]);
		y++;
	}
	get_map()->len = y;
	get_map()->tile_size = MINIMAP_SIZE / get_map()->width;
	if (get_map()->len > get_map()->width)
		get_map()->tile_size = MINIMAP_SIZE / get_map()->len;
}

void	fill_rows_with_spaces(char **data)
{
	int		y;
	int		x;
	char	*new;

	y = 0;
	while (data != NULL && data[y] != NULL)
	{
		x = 0;
		new = ft_calloc(get_map()->width + 2, sizeof(*new));
		if (new == NULL)
			put_error_and_exit("malloc error in fill_rows_with_spaces()");
		while (data[y][x] != '\0')
		{
			new[x] = data[y][x];
			x++;
		}
		while (x <= get_map()->width)
			new[x++] = ' ';
		new[x] = '\0';
		ft_free((void **)(&data[y]));
		data[y] = new;
		y++;
	}
}

void	print_map(void)
{
	int	index;

	index = 0;
	printf("FLOOR COLOUR = %x\n", get_style()->floor_color);
	printf("CEILING COLOUR = %x\n", get_style()->ceiling_color);
	printf("x_max = %d\n", get_map()->width);
	printf("y_max = %d\n", get_map()->len);
	printf("tile_size = %d\n", get_map()->tile_size);
	printf("\n____________________\nPLAYER INFOS\n");
	printf("Player direction = %f\n", get_player()->direction);
	printf("Player starts at = (%f|%f)\n", get_player()->x_pos,
		get_player()->y_pos);
	printf("\n___________________\nMAP:\n");
	if (get_map()->data == NULL)
	{
		printf("get_map()->data is null!!!\n");
		return ;
	}
	while (get_map()->data[index] != NULL)
	{
		printf("|%s|\n", get_map()->data[index]);
		index++;
	}
}
