#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>

void	count_dimensions(char **data);
void	fill_rows_with_spaces(char **data);
void	print_map(void);

int	parse_map(void)
{
	count_dimensions(map()->data);
	fill_rows_with_spaces(map()->data);
	if (map_check(map()->data) || player_check(map()->data))
		return (EXIT_FAILURE);
	printf("\nprint_map()........\n");
	
	print_map();
	return (1);
}

void	count_dimensions(char **data)
{
	int	y;

	y = 0;
	while (data != NULL && data[y] != NULL)
	{
		if (map()->width < ft_strlen(data[y]))
			map()->width = ft_strlen(data[y]);
		y++;
	}
	map()->len = y;
	map()->box_size = MINIMAP_SIZE / map()->width;
	if (map()->len > map()->width)
		map()->box_size = MINIMAP_SIZE / map()->len;
}

void	fill_rows_with_spaces(char **data)
{
	int		y;
	int		x;
	char	*new;

	y = 0;
	while (data != NULL && data[y] != NULL)
	{
		if (ft_strlen(data[y]) < map()->width)
		{
			x = 0;
			new = ft_calloc(map()->width + 1, sizeof(*new));
			if (new == NULL)
				put_error_and_exit("malloc error in fill_rows_with_spaces()", 1);
			while (data[y][x] != '\0')
			{
				new[x] = data[y][x];
				x++;
			}
			while (x < map()->width)
				new[x++] = ' ';
			ft_free((void **)(&data[y]));
			data[y] = new;
		}
		y++;
	}
	return ;
}

void	print_map(void)
{
	int	index;

	index = 0;
	printf("NORTH = %s\n", style()->north_walls);
	printf("EAST = %s\n", style()->east_walls);
	printf("SOUTH = %s\n", style()->south_walls);
	printf("WEST = %s\n", style()->west_walls);
	printf("FLOOR COLOUR = %x\n", style()->floor_color);
	printf("CEILING COLOUR = %x\n", style()->ceiling_color);
	printf("x_max = %d\n", map()->width);
	printf("y_max = %d\n", map()->len);
	printf("box_size = %d\n", map()->box_size);
	printf("\n____________________\nPLAYER INFOS\n");
	printf("Player direction = %f\n", player()->direction);
	printf("Player starts at = (%d|%d)\n", player()->x_pos, player()->y_pos);
	printf("\n___________________\nMAP:\n");
	if (map()->data == NULL)
	{
		printf("map()->data is null!!!\n");
		return ;
	}
	while (map()->data[index] != NULL)
	{
		printf("|%s|\n", map()->data[index]);
		index++;
	}
	return ;
}
