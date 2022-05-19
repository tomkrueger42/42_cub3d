#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

unsigned int	convert_color(char *value);
char			*extract_value(char *lines, char *name);
char			*find_map(char *string);

void	read_file(char *filename)
{
	int		fd;
	char	*lines;
	char	*temp;

	fd = open(filename, O_RDONLY);
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		lines = ft_strjoin_free(lines, temp);
		temp = get_next_line(fd);
	}
	close (fd);
	style()->north_walls = extract_value(lines, "NO ");
	style()->east_walls = extract_value(lines, "EA ");
	style()->south_walls = extract_value(lines, "SO ");
	style()->west_walls = extract_value(lines, "WE ");
	style()->floor_color = convert_color(extract_value(lines, "F "));
	style()->ceiling_color = convert_color(extract_value(lines, "C "));
	// if (find_map(lines) == -1)
	// 	put_error_and_exit("couldn't find map", 2);
	map()->data = ft_split(find_map(lines), '\n');
	ft_free((void **)(&lines));
}

t_style	*style(void)
{
	static t_style	*style;

	if (style == NULL)
	{
		style = ft_calloc(1, sizeof(t_style));
		if (style == NULL)
			put_error_and_exit("malloc failure in style()", 1);
	}
	return (style);
}

unsigned int	convert_color(char *value)
{
	if (value == NULL)
		return (0);
	return (create_trgb(255, ft_atoi(value), ft_atoi(ft_strchr(value, ',') + 1),
			ft_atoi(ft_strrchr(value, ',') + 1)));
}

char	*extract_value(char *lines, char *name)
{
	int		end;
	char	*origin;

	origin = ft_strnstr(lines, name, ft_strlen(lines));
	if (origin == NULL)
		put_error_and_exit("invalid file!", 2);
	while (!ft_iswhitespace(*origin))
		origin++;
	while (ft_iswhitespace(*origin))
		origin++;
	end = 0;
	while (origin[end] != '\0' && !ft_iswhitespace(origin[end]))
		end++;
	return (ft_substr(origin, 0, end));
}

bool	valid_line(char *line)
{
	size_t	index;

	index = 0;
	while (line[index] != '\0' && line[index] != '\n')
	{
		if (ft_strchr(MAP_CHARS, line[index]))
			index++;
		else
			return (false);
	}
	return (true);
}

char	*find_map(char *lines)
{
	char	*line;
	char	*map_start;

	line = lines;
	while (*line != '\0' && valid_line(line) == false)
	{
		line = ft_strchr(line, '\n') + 1;
	}
	map_start = line;
	while (*line != '\0')
	{
		if (valid_line(line) == false)
			put_error_and_exit("invalid map", 2);
		if (ft_strchr(line, '\n'))
			line = ft_strchr(line, '\n') + 1;
		else
			break ;
	}
	return (map_start);
}