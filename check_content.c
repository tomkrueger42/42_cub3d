
int	check_top(char **maplines, t_vector2_int pos, char checkchar)
{
	int	length_top;
	int	length_middle;

	if (pos.y == 0)
		return (0);
	length_top = (int)ft_strlen(maplines[pos.y - 1]);
	length_middle = (int)ft_strlen(maplines[pos.y]);
	if (length_top - 3 < pos.x)
		return (1);
	if ((length_top >= length_middle \
		&& maplines[pos.y - 1][pos.x] != '1' \
		&& maplines[pos.y - 1][pos.x] != checkchar \
		&& !is_valid_c(maplines[pos.y - 1][pos.x])) \
		|| (length_top >= length_middle - 1 && pos.x != 0 \
		&& maplines[pos.y - 1][pos.x - 1] != '1' \
		&& maplines[pos.y - 1][pos.x - 1] != checkchar \
		&& !is_valid_c(maplines[pos.y - 1][pos.x - 1])) \
		|| (length_top >= length_middle + 1 && pos.x + 1 < length_top \
		&& maplines[pos.y - 1][pos.x + 1] != '1' \
		&& maplines[pos.y - 1][pos.x + 1] != checkchar \
		&& !is_valid_c(maplines[pos.y - 1][pos.x + 1])))
		return (1);
	else
		return (0);
}

int	check_bot(t_vars *vars, char **maplines, t_vector2_int pos, char checkchar)
{
	int	length_bot;
	int	length_middle;

	if (pos.y == vars->map->n_lines - 1)
		return (0);
	length_bot = (int)ft_strlen(maplines[pos.y + 1]);
	length_middle = (int)ft_strlen(maplines[pos.y]);
	if (length_bot - 2 < pos.x)
		return (1);
	if ((length_bot >= length_middle && maplines[pos.y + 1][pos.x] != '1' \
		&& (maplines[pos.y + 1][pos.x] != checkchar) \
		&& !is_valid_c(maplines[pos.y + 1][pos.x])) \
		|| (length_bot >= length_middle - 1 && pos.x != 0 \
		&& maplines[pos.y + 1][pos.x - 1] != '1' \
		&& maplines[pos.y + 1][pos.x - 1] != checkchar \
		&& !is_valid_c(maplines[pos.y + 1][pos.x - 1])) \
		|| (length_bot >= pos.x + 1 \
		&& maplines[pos.y + 1][pos.x + 1] != '1' \
		&& maplines[pos.y + 1][pos.x + 1] != checkchar \
		&& !is_valid_c(maplines[pos.y + 1][pos.x + 1])))
		return (1);
	else
		return (0);
}

int	check_lr(char **maplines, t_vector2_int pos, char checkchar)
{
	int	length_middle;

	length_middle = (int)ft_strlen(maplines[pos.y]);
	if ((pos.x != 0 \
		&& maplines[pos.y][pos.x - 1] != '1' \
		&& maplines[pos.y][pos.x - 1] != checkchar \
		&& !is_valid_c(maplines[pos.y][pos.x - 1])) \
		|| ((pos.x + 1 < length_middle
		&& maplines[pos.y][pos.x + 1] != '1' \
		&& maplines[pos.y][pos.x + 1] != checkchar) \
		&& pos.x < length_middle - 2 \
		&& !is_valid_c(maplines[pos.y][pos.x + 1])))
		return (1);
	else
		return (0);
}

//Checks with spaces
int	check_top_space(char **maplines, t_vector2_int pos)
{
	int	length_top;
	int	length_middle;

	if (pos.y == 0)
		return (0);
	length_top = (int)ft_strlen(maplines[pos.y - 1]) - 1;
	length_middle = (int)ft_strlen(maplines[pos.y]);
	if ((length_top > pos.x \
		&& maplines[pos.y - 1][pos.x] != '1' \
		&& maplines[pos.y - 1][pos.x] != ' ') \
		|| (length_top - 1 > pos.x - 1 && pos.x != 0 \
		&& maplines[pos.y - 1][pos.x - 1] != '1' \
		&& maplines[pos.y - 1][pos.x - 1] != ' ') \
		|| (length_top > pos.x + 1 && pos.x + 1 < length_top \
		&& maplines[pos.y - 1][pos.x + 1] != '1' \
		&& maplines[pos.y - 1][pos.x + 1] != ' '))
		return (1);
	else
		return (0);
}

int	check_bot_space(t_vars *vars, char **maplines, t_vector2_int pos)
{
	int	length_bot;
	int	length_middle;

	if (pos.y == vars->map->n_lines - 1)
		return (0);
	length_bot = (int)ft_strlen(maplines[pos.y + 1]) - 1;
	length_middle = (int)ft_strlen(maplines[pos.y]);
	if ((length_bot > pos.x && maplines[pos.y + 1][pos.x] != '1' \ //a
		&& (maplines[pos.y + 1][pos.x] != ' ')) \
		|| (length_bot - 1 > pos.x - 1 && pos.x != 0 \   //links/rechts schraeg unter dem space duerfen nur 1 oder space sein
		&& maplines[pos.y + 1][pos.x - 1] != '1' \
		&& maplines[pos.y + 1][pos.x - 1] != ' ') \
		|| (length_bot > pos.x + 1 \
		&& maplines[pos.y + 1][pos.x + 1] != '1' \
		&& maplines[pos.y + 1][pos.x + 1] != ' '))
		return (1);
	else
		return (0);
}

static int	check_lr_space(char **maplines, t_vector2_int pos)
{
	int	length_middle;

	length_middle = (int)ft_strlen(maplines[pos.y]) - 2;
	if ((pos.x != 0 \
		&& maplines[pos.y][pos.x - 1] != '1' \
		&& maplines[pos.y][pos.x - 1] != ' ') \
		|| ((pos.x < length_middle
		&& maplines[pos.y][pos.x + 1] != '1' \
		&& maplines[pos.y][pos.x + 1] != ' ') \
		))
		return (1);
	else
		return (0);
}

static int	check_valid_chars(t_vars *vars, char **maplines, t_vector2_int pos)
{
	if (!check_bot(vars, maplines, pos, '0') \
		&& !check_top(maplines, pos, '0') \
		&& !check_lr(maplines, pos, '0'))
		return (0);
	return (1);
}


static int	check_square(t_vars *vars, char **maplines, t_vector2_int pos)
{
	if ((maplines[pos.y][pos.x] == ' '
		&& (check_bot_space(vars, maplines, pos) \
		|| check_top_space(maplines, pos) \
		|| check_lr_space(maplines, pos))) \
		||
		((maplines[pos.y][pos.x] == '0' \
		|| maplines[pos.y][pos.x] == 'N' \
		|| maplines[pos.y][pos.x] == 'S' \
		|| maplines[pos.y][pos.x] == 'E' \
		|| maplines[pos.y][pos.x] == 'W') \
		&& check_valid_chars(vars, maplines, pos)))
	{
		printf("Error\nMap: Incorrect format at (x: %d, y: %d) \
not enclosed by walls\n", pos.x, pos.y);
		return (1);
	}
	return (0);
}

int	check_map(t_vars *vars, char **maplines)
{
	t_vector2_int	pos;
	int				spawncnt;

	pos.y = 0;
	pos.x = 0;
	spawncnt = 0;
	while (maplines[pos.y])
	{
		while (maplines[pos.y][pos.x])
		{
			if (check_square(vars, maplines, pos))
				return (1);
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
	return (0);
}