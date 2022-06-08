#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>

bool	valid_line(char *line);

// This function searches for the first valid line of the map and if there is 
// ANY NON VALID line afterwards it says 'invalid map'
char	*find_map(char *lines)
{
	char	*line;
	char	*map_start;

	line = lines;
	while (*line != '\0' && valid_line(line) == false)
	{
		line = ft_strchr(line, '\n') + 1;
	}
	map_start = line;
	while (*line != '\0')
	{
		if (valid_line(line) == false)
			put_error_and_exit("invalid map", 2);
		if (ft_strchr(line, '\n'))
			line = ft_strchr(line, '\n') + 1;
		else
			break ;
	}
	return (map_start);
}

// This function checks if a line of the map is valid
bool	valid_line(char *line)
{
	size_t	index;

	index = 0;
	while (line[index] != '\0' && line[index] != '\n')
	{
		if (ft_strchr(MAP_CHARS, line[index]))
			index++;
		else
			return (false);
	}
	return (true);
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
	fill_rows_with_spaces(data);
}

void	fill_rows_with_spaces(char **data)
{
	int		y;
	int		x;
	char	*new;

	y = 0;
	while (data != NULL && data[y] != NULL)
	{
		if (ft_strlen(data[y]) < get_map()->width)
		{
			x = 0;
			new = ft_calloc(get_map()->width + 1, sizeof(*new));
			if (new == NULL)
				put_error_and_exit("malloc error in fill_rows_with_spaces()", 1);
			while (data[y][x] != '\0')
			{
				new[x] = data[y][x];
				x++;
			}
			while (x < get_map()->width)
				new[x++] = ' ';
			ft_free((void **)(&data[y]));
			data[y] = new;
		}
		y++;
	}
}

void	print_map(void)
{
	int	index;

	index = 0;
	printf("NORTH = %s\n", get_style()->north_walls);
	printf("EAST = %s\n", get_style()->east_walls);
	printf("SOUTH = %s\n", get_style()->south_walls);
	printf("WEST = %s\n", get_style()->west_walls);
	printf("FLOOR COLOUR = %x\n", get_style()->floor_color);
	printf("CEILING COLOUR = %x\n", get_style()->ceiling_color);
	printf("x_max = %d\n", get_map()->width);
	printf("y_max = %d\n", get_map()->len);
	printf("tile_size = %d\n", get_map()->tile_size);
	printf("\n____________________\nPLAYER INFOS\n");
	printf("Player direction = %f\n", get_player()->direction);
	printf("Player starts at = (%f|%f)\n", get_player()->x_pos, get_player()->y_pos);
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
	return ;
}
