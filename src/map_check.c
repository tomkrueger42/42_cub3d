#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int		blanks_nearby(char **data, int x, int y);
int		player_check(char **data);
void	populate_player(int x, int y, char heading);



/*
 ausser beim ersten Zeichen
 links neben einem space muss eine 1 oder ein space sein
 rechts neben einem space muss eine 1 oder ein space sein
*/
static int	check_lr_space(char **maplines, int x, int y)
{
	int	length_middle;

	length_middle = (int)ft_strlen(maplines[y]) - 2;
	if ((x != 0 \
		&& maplines[y][x - 1] != '1' \
		&& maplines[y][x - 1] != ' ') \
		|| ((x < length_middle                       
		&& maplines[y][x + 1] != '1' \
		&& maplines[y][x + 1] != ' ') \
		))
		return (1);
	else
		return (0);
}



int	check_top_space(char **maplines, int x, int y)
{
	int	length_top;
	int	length_middle;

	if (y == 0)
		return (0);
	length_top = (int)ft_strlen(maplines[y - 1]) - 1;
	length_middle = (int)ft_strlen(maplines[y]);
	if ((length_top > x \
		&& maplines[y - 1][x] != '1' \
		&& maplines[y - 1][x] != ' ') \
		|| (length_top - 1 > x - 1 && x != 0 \
		&& maplines[y - 1][x - 1] != '1' \
		&& maplines[y - 1][x - 1] != ' ') \
		|| (length_top > x + 1 && x + 1 < length_top \
		&& maplines[y - 1][x + 1] != '1' \
		&& maplines[y - 1][x + 1] != ' '))
		return (1);
	else
		return (0);
}


/*
siehe notizen
*/
int	check_bot_space(char **maplines, int x, int y)
{
	int	length_bot;
	int	length_middle;

	if (y == get_map()->len - 1)
		return (0);
	length_bot = (int)ft_strlen(maplines[y + 1]) - 1;
	length_middle = (int)ft_strlen(maplines[y]);
	if ((length_bot > x && maplines[y + 1][x] != '1' \
		&& (maplines[y + 1][x] != ' ')) \
		|| (length_bot - 1 > x - 1 && x != 0 \
		&& maplines[y + 1][x - 1] != '1' \
		&& maplines[y + 1][x - 1] != ' ') \
		|| (length_bot > x + 1 \
		&& maplines[y + 1][x + 1] != '1' \
		&& maplines[y + 1][x + 1] != ' '))
		return (1);
	else
		return (0);
}

int check_square(char **maplines, int x, int y)
{
    if ((maplines[y][x] == ' '
		&& (check_bot_space(maplines, x, y) \
		|| check_top_space(maplines, x, y) \
		|| check_lr_space(maplines, x, y))))
    {
        printf("Error\nMap: Incorrect format at (x: %d, y: %d) \
                not enclosed by walls\n", x, y);
		return (1);
	}
	return (0);
}

/*
	checks top and bottom
*/
static int	check_top_bot(char **maplines)
{
	int	y;
	int	x;

	y = get_map()->len - 1;
	printf("the map has %d lines", y);   // remove later on
	x = 0;
	while (maplines[0][x] && x < (int)ft_strlen(maplines[0]) - 2)
	{
		if (maplines[0][x] != '1' && maplines[0][x] != ' ')
		{
			printf("Error\nMap: not inclosed in walls 1(x: %d, y: %d)\n", x, 0);
			return (1);
		}
		x++;
	}
	x = 0;
	while (maplines[y][x] && x < (int)ft_strlen(maplines[y]) - 2)
	{
		if (maplines[y][x] != '1' && maplines[y][x] != ' ')
		{
			printf("Error\nMap: not inclosed in walls 2(x: %d, y: %d)\n", x, y);
			return (1);
		}
		x++;
	}
	return (0);
}

/*
	gets str_len of maplines and subtracts newline and whitespace until encounters first char from behind and cheks if it is wall
*/
static int	check_back(char	**maplines, int y)
{
	int	i;
	int	str_len;

	i = 0;
	str_len = (int)ft_strlen(maplines[y]) - 1;
	while (maplines[y][str_len - i]
		&& maplines[y][str_len - i] == '\n')
			i++;
	while (maplines[y][str_len - i]
		&& maplines[y][str_len - i] == ' ')
			i++;
	if (maplines[y][str_len - i] != '1')
	{
		printf("Error\nMap: not inclosed in walls 3(x: %d, y: %d)\n", \
		str_len - i, y);
		return (1);
	}
	return (0);
}

/*
	skips the whitespace until it finds first char and checks if it is a wall
*/
static int	check_front(char **maplines, int y)
{
	int x;

	x = 0;
	while (maplines[y][x] && maplines[y][x] == ' ')
		x++;
	if (maplines[y][x] != '1')
	{
		printf("x is : %d\n", x);
		printf("Error\nMap: not inclosed in walls 4(x: %d, y: %d)\n", x, y);
		return (1);
	}
	return (0);
}

int		check_borders(char **maplines)
{
	int y;

	y = 0;
	while (maplines[y])
	{
		if (check_front(maplines, y)
			|| check_back(maplines, y))
			return (1);
		//printf("y is : %d\n", y);
		y++;
	}
	if (check_top_bot(maplines))
		return (1);
	return (0);
}

void	prints_map(char **maplines)
{
	int i = 0;
	while (maplines[i])
	{
		printf("%s\n", maplines[i]);
		i++;
	}
}

int		check_spaces(char **maplines)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (maplines[y])
	{
		while (maplines[y][x])
		{
			if (check_square(maplines, x, y))
				return (1);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

/*
	map-check gets the map-data from get_map()->data, the map is saved and filled with spaces
	it will check the boarders with check-boraders
*/
int		map_check(char **data)
{
	prints_map(data);
	if (check_borders(data) || check_spaces(data))
		return (1);
	return (0);
}

/* int	map_check(char **data)
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
} */

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
