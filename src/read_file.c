#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

unsigned int	convert_color(char *value);
char			*extract_value(char *lines, char *identifier);
mlx_texture_t	*load_texture(char *value);

void	read_file(char *filename)
{
	int		fd;
	char	*lines;
	char	*temp;
	t_style	*style;

	lines = NULL;
	fd = open(filename, O_RDONLY);
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		lines = ft_strjoin_free(lines, temp);
		temp = get_next_line(fd);
	}
	close (fd);
	style = get_style();
	style->texture[NORTH] = load_texture(extract_value(lines, "NO"));
	style->texture[EAST] = load_texture(extract_value(lines, "EA"));
	style->texture[SOUTH] = load_texture(extract_value(lines, "SO"));
	style->texture[WEST] = load_texture(extract_value(lines, "WE"));
	style->floor_color = convert_color(extract_value(lines, "F "));
	style->ceiling_color = convert_color(extract_value(lines, "C "));
	printf("find_map: %p, %s", find_map(lines), find_map(lines));
	get_map()->data = ft_split(find_map(lines), '\n');
	if (get_map()->data == NULL)
		put_error_and_exit("no map!", 1);
	ft_free((void **)(&lines));
}


int		texture_given(char *lines, char *identifier)
{
	bool	sw;
	sw = false;
	while (true)
	{

		lines = ft_strnstr(lines, identifier, ft_strlen(lines));
		if (lines == NULL)
			break;
		else if (sw == true)
			return (1);
		sw = true;
		lines += ft_strlen(identifier);
	}
	return (0);
}

// This function extracts the value of the identifier from lines
char	*extract_value(char *lines, char *identifier)
{
	int		end;
	char	*origin;

	if (texture_given(lines, identifier))
		put_error_and_exit("You cant have multiple paths for one texture!", 2);
	origin = ft_strnstr(lines, identifier, ft_strlen(lines));
	//printf("origin is%s\n", origin);
	if (origin == NULL)
		put_error_and_exit("invalid file!", 2);
	while (!ft_iswhitespace(*origin))
		origin++;
	while (ft_iswhitespace(*origin))
		origin++;
	end = 0;
	while (origin[end] != '\0' && !ft_iswhitespace(origin[end]))
		end++;
	printf("output is %s\n", ft_substr(origin, 0, end));
	return (ft_substr(origin, 0, end));
}

mlx_texture_t	*load_texture(char *value)
{
	mlx_texture_t	*texture;

	if (value == NULL)
		put_error_and_exit("missing texture path", 1);
	texture = mlx_load_png(value);
	ft_free((void **)&value);
	if (texture == NULL)
		put_error_and_exit("incorrect texture path", 1);
	return (texture);
}

// This function converts the comma seperated rgb values to hex
unsigned int	convert_color(char *value)
{
	unsigned int	color;
	int				i;

	i = 0;
	if (value == NULL)
		put_error_and_exit("missing floor/ceiling color", 1);
	while (value[i] != '\0')
	{
		if (!ft_isdigit(value[i]) && value[i] != ',')
			put_error_and_exit("wrong color code formatting", 1);
		i++;
	}
	if (ft_count_char(value, ',') > 2)
		put_error_and_exit("incorrect number formatting", 1);
	if (ft_atoi(value) > 255 || ft_atoi(value) < 0)
		put_error_and_exit("color range needs to be between 0 and 255", 1);
	if (ft_atoi(ft_strchr(value, ',') + 1) > 255 || ft_atoi(ft_strchr(value, ',') + 1) < 0)
		put_error_and_exit("color range needs to be between 0 and 255", 1);
	if (ft_atoi(ft_strrchr(value, ',') + 1) > 255 || ft_atoi(ft_strrchr(value, ',') + 1) < 0)
		put_error_and_exit("color range needs to be between 0 and 255", 1);
	color = create_trgb(0, ft_atoi(value), ft_atoi(ft_strchr(value, ',') + 1),
			ft_atoi(ft_strrchr(value, ',') + 1));
	ft_free((void **)&value);
	return (color);
}
