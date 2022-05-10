#include "map.h"

t_map	*make_struct(char *lines, int x, int y);
void	*fill_struct(char *lines, t_map *map);
t_map	*read_map(char *src);

/* 
	liest alles in einen langen string, der spaeter ausgewertet wird
	kennt ausserdem die groesse der map
	sollte im return t_map aufrufen
*/
t_map	*read_map(char *src)
{
	int		fd;
	int		x;
	int		y;
	char	*lines;
	char	*temp;

	lines = NULL;
	fd = open(src);
	temp = get_next_line(fd);
	if (temp != NULL)
		y = 1;
	x = ft_strlen(temp);
	while (temp != NULL)
	{
		lines = ft_strjoin_free(lines, temp);
		temp = get_next_line(fd);
		if (ft_strlen(temp) > x)
			x = ft_strlen(temp);
		y++;
	}
	close (fd);
	return (make_struct(lines, x, y));
}

t_map	*make_struct(char *lines, int x, int y)
{
	t_map	*new;

	new = malloc(sizeof(t_map *));
	if (new == NULL)
		return (NULL);
	new->n = NULL;
	new->s = NULL;
	new->e = NULL;
	new->w = NULL;
	new->f = NULL;
	new->x_max = x;
	new->y_max = y;
	fill_struct(lines, new);
	free(lines);
	return (new);
}

void	*fill_struct(char *lines, t_map *map)
{
	int	ct;

	ct = 0;
	while (ft_iswhitespace(lines[ct]))
		ct++;
	if (lines[ct] = 'N' && lines[ct + 1] == 'O')
		return ;
	/*
	fuellen der anderen variablen
	*/
	map->map = ft_split(lines, '\n');
	return ;
}
