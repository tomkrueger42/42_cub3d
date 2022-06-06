#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int		blanks_nearby(char **data, int x, int y);
int		player_check(char **data);
void	populate_player(int x, int y, char heading);

int	map_check(char **data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (data[y] != NULL)
	{
		while (data[y][x] != '\0')
		{
			if (data[y][x] == '0' && blanks_nearby(data, x, y))
			{
				printf("unclosed walls near map[%d][%d]\n", y, x);
				put_error_and_exit("unclosed walls", 3);
				return (EXIT_FAILURE);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (EXIT_SUCCESS);
}

int	blanks_nearby(char **data, int x, int y) // segfault when longest map->data line ends with 0 and no blanks nearby
{
	if (x == 0 || y == 0
		|| data[y - 1][x - 1] == ' '
		|| data[y - 1][x] == ' '
		|| data[y - 1][x + 1] == ' '
		|| data[y][x - 1] == ' '
		|| data[y][x] == ' '
		|| data[y][x + 1] == ' '
		|| data[y + 1][x - 1] == ' '
		|| data[y + 1][x] == ' '
		|| data[y + 1][x + 1] == ' ')
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	player_check(char **data)
{
	int	x;
	int	y;
	int	sum;

	y = 0;
	sum = 0;
	while (data[y] != NULL)
	{
		x = 0;
		while (data[y][x] != '\0')
		{
			if (data[y][x] == 'N' || data[y][x] == 'E'
				|| data[y][x] == 'S' || data[y][x] == 'W')
			{
				if (y == get_map()->len || x == get_map()->width || blanks_nearby(data, x, y))
					put_error_and_exit("incorrect player positioning", 3);
				populate_player(x, y, data[y][x]);
				sum++;
			}
			x++;
		}
		y++;
	}
	if (sum != 1)
		put_error_and_exit("wrong amount of players", 3);
	return (EXIT_SUCCESS);
}

void	populate_player(int x, int y, char heading)
{
	get_player()->y_pos = y + 0.5;
	get_player()->x_pos = x + 0.5;
	if (heading == 'N')
		get_player()->direction = 1.5 * PI;
	else if (heading == 'E')
		get_player()->direction = 0;
	else if (heading == 'S')
		get_player()->direction = 0.5 * PI;
	else if (heading == 'W')
		get_player()->direction = PI;
	get_player()->size = get_map()->tile_size * 2 / 3;
	get_player()->x_delta = cos(get_player()->direction);
	get_player()->y_delta = sin(get_player()->direction);
	get_player()->speed = (double)1 / (double)MOVEMENT_SPEED;
}
