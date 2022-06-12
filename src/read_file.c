#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

unsigned int	convert_color(char *value);
char			*extract_value(char *lines, char *identifier);
void			load_texture(int *texture, char *path);

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
	style->texture[0] = mlx_load_png(extract_value(lines, "NO "));
	style->texture[1] = mlx_load_png(extract_value(lines, "EA "));
	style->texture[2] = mlx_load_png(extract_value(lines, "SO "));
	style->texture[3] = mlx_load_png(extract_value(lines, "WE "));
	style->floor_color = convert_color(extract_value(lines, "F "));
	style->ceiling_color = convert_color(extract_value(lines, "C "));
	get_map()->data = ft_split(find_map(lines), '\n');
	ft_free((void **)(&lines));
}

// This function extracts the value of the identifier from lines
char	*extract_value(char *lines, char *identifier)
{
	int		end;
	char	*origin;

	origin = ft_strnstr(lines, identifier, ft_strlen(lines));
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

// This function converts the comma seperated rgb values to hex
unsigned int	convert_color(char *value)
{
	if (value == NULL)
		return (0);
	return (create_trgb(0, ft_atoi(value), ft_atoi(ft_strchr(value, ',') + 1),
			ft_atoi(ft_strrchr(value, ',') + 1)));
}
