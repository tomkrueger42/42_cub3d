#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


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
        printf("error is at bot space");
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