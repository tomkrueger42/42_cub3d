#ifndef MAP_MAP_H
# define MAP_MAP_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# include "../libs/libft/includes/libft.h"

/*
N = 0.5
S = 1.5
W = 1;
E = 0
*/

typedef struct s_player {
	char	direction;	 // direction looking to
//	double	direction;
	int		start_x;
	int		start_y;
}	t_player;

typedef struct s_map {
	char		*n; //pic path north
	char		*s; //pic path south
	char		*w; //pic path west
	char		*e; //pic path east
	char		*f; // floor colour
	char		*c; // ceiling colour
	t_player	player;
	int			x_max; // while strlen < x_max char append mit ' '
	int			y_max;
	char		**map;
}	t_map;


/* read.c */

t_map	*make_struct(char *lines, int x);
void	fill_struct(char *lines, t_map *map);
t_map	*read_map(char *src);

/* free_map.c */

void	free_map(t_map *map);

/* helper.c */

int		valid_line(char *string, int potenz);
int		find_code(char *origin, char *needle);
int		find_map(char *string);



#endif
/*
The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the player’s start position and spawning
orientation.

The map must be closed/surrounded by walls, if not the program must return
an error.

◦ Except for the map content, each type of element can be separated by one or
more empty line(s).

◦ Except for the map content which always has to be the last, each type of
element can be set in any order in the file.

◦ Except for the map, each type of information from an element can be separated
by one or more space(s).

◦ The map must be parsed as it looks in the file. Spaces are a valid part of the
map and are up to you to handle. You must be able to parse any kind of map,
as long as it respects the rules of the map.

Each element (except the map) firsts information is the type identifier (com-
posed by one or two character(s)), followed by all specific informations for each
object in a strict order such as :
∗ North texture:
NO ./path_to_the_north_texture
· identifier: NO
· path to the north texure
∗ South texture:
SO ./path_to_the_south_texture
· identifier: SO
· path to the south texure
∗ West texture:
WE ./path_to_the_west_texture
· identifier: WE
· path to the west texure
∗ East texture:
EA ./path_to_the_east_texture
· identifier: EA
· path to the east texure
∗ Floor color:
F 220,100,0
· identifier: F
· R,G,B colors in range [0,255]: 0, 255, 255

If any misconfiguration of any kind is encountered in the file, the program
must exit properly and return "Error\n" followed by an explicit error message
of your choice.
*/