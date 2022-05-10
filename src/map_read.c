#include "map_map.h"

t_map	*make_struct(char *lines, int x, int y);
void	fill_struct(char *lines, t_map *map);
t_map	*read_map(char *src);
char	*fill_var(char *lines, char *name);


/* 
	liest alles in einen langen string, der spaeter ausgewertet wird
	kennt ausserdem die groesse der map
	sollte im return t_map aufrufen
	das x und y kann ich vllt auch der ft_split entnehmen
*/
t_map	*read_map(char *src)
{
	int		fd;
	int		x;
	int		y;
	char	*lines;
	char	*temp;

	lines = NULL;
	fd = open(src, O_RDONLY);
	temp = get_next_line(fd);
	if (temp == NULL)
	{
		close (fd);
		return (NULL);
	}
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

/*
	macht einen grundmalloc und setzt die werte per default auf NULL
	das macht die errorpruefung leichter
*/
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
	new->c = NULL;
	new->map = NULL;
	new->player = 0;
	new->x_max = x;
	new->y_max = y;
	fill_struct(lines, new);
	ft_free((void **)(&lines));
	return (new);
}

void	fill_struct(char *lines, t_map *map)
{
	int		ct;
	char	*temp;

	map->n = fill_var(lines, "NO ");
	map->s = fill_var(lines, "SO ");
	map->e = fill_var(lines, "EA ");
	map->w = fill_var(lines, "WE ");
	map->c = fill_var(lines, "C ");
	map->f = fill_var(lines, "F ");
	temp = lines;
	ct = find_map(temp);
	printf("ct = %d\n", ct);
	if (ct > -1)
		map->map = ft_split(temp + ct, '\n'); // ich beginne zu frueh
	/*
	irgendwie scheint mir dieses konstrukt noch reichlich fehleranfaellig (JAAAA!)
	ct auf beginn der map setzen - iwie
	ich brauche eine funktion, mit der ich ermittle, ab wann  die eigentliche map beginnt
	darf nur whitespace oder digit sein in der zeile
	*/
	return ;
}

/*
	der versuch, eine funktion zu schreiben, 
	die mir alle variablen befuellen kann
*/
char	*fill_var(char *lines, char *name)
{
	int		end;
	int		begin;
	char	*temp;

	begin = find_code(lines, name);
	if (begin == -1)
		return (NULL);
	while (ft_iswhitespace(lines[begin]))
		begin++;
	end = begin;
	while (lines[end] != '\0' && lines[end] != '\n')
		end++;
	temp = ft_substr(lines, begin, (end - begin));
	return (temp);
}
