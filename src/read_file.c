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

	lines = NULL;
	fd = open(filename, O_RDONLY);
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		lines = ft_strjoin_free(lines, temp);
		temp = get_next_line(fd);
	}
	close (fd);
	get_style()->north_walls = extract_value(lines, "NO ");
	get_style()->east_walls = extract_value(lines, "EA ");
	get_style()->south_walls = extract_value(lines, "SO ");
	get_style()->west_walls = extract_value(lines, "WE ");
	get_style()->floor_color = convert_color(extract_value(lines, "F "));
	get_style()->ceiling_color = convert_color(extract_value(lines, "C "));
	load_texture(get_style()->textures[0], get_style()->north_walls);
	load_texture(get_style()->textures[1], get_style()->east_walls);
	load_texture(get_style()->textures[2], get_style()->south_walls);
	load_texture(get_style()->textures[3], get_style()->west_walls);
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

void	load_texture(int *texture, char *path)
{
	t_imgint tex_img;
	int	x;
	int	y;

	tex_img.img = mlx_xpm_file_to_image(get_graphics()->mlx, path, \
		&tex_img.img_width, &tex_img.img_height);
	tex_img.addr = (int *)mlx_get_data_addr(tex_img.img, &tex_img.bits_per_pixel, \
		&tex_img.line_length, &tex_img.endian);
	y = -1;
	while (++y < tex_img.img_height)
	{
		x = -1;
		while (++x < tex_img.img_width)
			texture[tex_img.img_height * y + x] = \
				tex_img.addr[tex_img.img_height * y + x];
	}
	mlx_destroy_image(get_graphics()->mlx, tex_img.img);
}
