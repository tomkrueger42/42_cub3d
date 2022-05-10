#include "map_map.h"

t_map	*make_struct(char *lines, int x, int y);
void	fill_struct(char *lines, t_map *map);
t_map	*read_map(char *src);
char	*fill_var(char *lines, char var, int ct);


/* 
	liest alles in einen langen string, der spaeter ausgewertet wird
	kennt ausserdem die groesse der map
	sollte im return t_map aufrufen
	das x und y kann ich vllt auch der ft_split entnehmen
*/
t_map	*read_map(char *src)
{
	printf("read_map \n");
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
	printf("make struct\n");
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
	new->player = 0;
	new->x_max = x;
	new->y_max = y;
	fill_struct(lines, new);
	ft_free((void **)(&lines));
	return (new);
}

void	fill_struct(char *lines, t_map *map)
{
	printf("fill_struct\n");
	int		ct;
	char	*temp;

	map->n = fill_var(lines, 'O', ft_strchr_int(lines, 'N'));
	map->s = fill_var(lines, 'O', ft_strchr_int(lines, 'S'));
	map->e = fill_var(lines, 'A', ft_strchr_int(lines, 'E'));
	map->w = fill_var(lines, 'E', ft_strchr_int(lines, 'W'));
	map->c = fill_var(lines, ' ', ft_strchr_int(lines, 'C'));
	ct = ft_strchr_int(lines, 'F');
	map->f = fill_var(lines, ' ', ct);
	/*
	irgendwie scheint mir dieses konstrukt noch reichlich fehleranfaellig (JAAAA!)
	ich muss strnstr verwenden oder so
	schliesslich koennte ein E schon in der ersten zeile als datei name stehen
	ct auf beginn der map setzen - iwie
	fuellen der anderen variablen
	*/
	temp = lines;
	temp = temp + ct;
	temp = temp + ft_strchr_int(temp, '\n');
	map->map = ft_split(lines + ct, '\n'); // ich beginne zu frueh
	// ich brauche eine funktion, mit der ich ermittle, ab wann  die eigentliche map beginnt
	// darf nur whitespace oder digit sein in der zeile
	return ;
}

/*
	der versuch, eine funktion zu schreiben, 
	die mir alle variablen befuellen kann
*/
char	*fill_var(char *lines, char var, int ct)
{
	printf("fill_var\n");
	int		end;
	char	*temp;

	printf("lines[ct] = %c\n", lines[ct]);
	if (lines[ct + 1] != var)
		return (NULL);
	if (var != ' ')
		ct = ct + 2;
	else
		ct++;
	while (ft_iswhitespace(lines[ct]))
		ct++;
	end = ct;
	while (lines[end] != '\0' && lines[end] != '\n')
		end++;
	temp = ft_substr(lines, ct, (end - ct));
	return (temp);
}
