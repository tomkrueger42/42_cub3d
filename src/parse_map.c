#include "cub3d.h"
#include <stdio.h>

void	count_dimensions(char **data);
void	fill_rows_with_spaces(char **data);
void	print_map(void);

bool	parse_map(void)
{
	count_dimensions(map()->data);
	fill_rows_with_spaces(map()->data);
	printf("\nprint_map........\n");
	
	print_map();
	return (1);
}

void	count_dimensions(char **data)
{
	size_t	y;

	y = 0;
	while (data != NULL && data[y] != NULL)
	{
		if (map()->width < ft_strlen(data[y]))
			map()->width = ft_strlen(data[y]);
		y++;
	}
	map()->len = ft_strlen(*data);
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
			new = ft_calloc(map()->len + 1, sizeof(*new));
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
	// printf("\n____________________\nPLAYER INFOS\n");
	// printf("Player direction = %f\n", map->player.direction);
	// printf("Player starts at = (%d|%d)\n", map->player.start_x, map->player.start_y);
	// printf("\n___________________\nMAP:\n");
	// if (map()->data == NULL)
	// {
	// 	printf("map()->data is null!!!\n");
	// 	return ;
	// }
	// while (map()->data[index] != NULL)
	// {
	// 	printf("|%s|\n", map()->data[index]);
	// 	index++;
	// }
	return ;
}
