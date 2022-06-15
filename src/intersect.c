#include "cub3d.h"
#include <math.h>

void			draw_tex(double dist, int col_index, t_draw draw, int wall_dir);
t_draw			get_tex_x(double angle, double radial, double dist,
					int wall_dir);
unsigned int	get_pixel(mlx_texture_t *tex, unsigned int pos);

void	fan_out(void)
{
	double	dist_hori;
	double	dist_verti;
	int		col_index;
	double	angle;
	double	radial;

	col_index = 0;
	radial = -FOV / 2;
	while (radial < FOV / 2)
	{
		angle = get_player()->direction + radial * RAD;
		dist_hori = cos(radial * RAD) * horizontal_intersections(angle);
		dist_verti = cos(radial * RAD) * vertical_intersections(angle);
		if (dist_hori < dist_verti && sin(angle) < 0)
			draw_tex(dist_hori, col_index, get_tex_x(angle, radial, dist_hori, NORTH), NORTH);
		else if (dist_verti < dist_hori && cos(angle) > 0)
			draw_tex(dist_verti, col_index,
				get_tex_x(angle, radial, dist_verti, EAST), EAST);
		else if (dist_hori < dist_verti && sin(angle) > 0)
			draw_tex(dist_hori, col_index,
				get_tex_x(angle, radial, dist_hori, SOUTH), SOUTH);
		else if (dist_verti < dist_hori && cos(angle) < 0)
			draw_tex(dist_verti, col_index,
				get_tex_x(angle, radial, dist_verti, WEST), WEST);
		col_index++;
		radial += (double)FOV / (double)WINDOW_WIDTH;
	}
}

void draw_tex(double dist, int col_index, t_draw draw, int wall_dir)
{
	int	y = 0;
	t_style	*style = get_style();
	t_graphics *graphics = get_graphics();

	draw.column_height = 1.0 / dist * WINDOW_HEIGHT;
	draw.step = (double)style->texture[wall_dir]->height / draw.column_height;
	draw.col_start = (WINDOW_HEIGHT - draw.column_height) / 2;
	if (draw.column_height > WINDOW_HEIGHT)
		draw.tex_pos = (draw.column_height - WINDOW_HEIGHT) / 2 * draw.step;
	else
		draw.tex_pos = draw.step;
	while (y < draw.col_start)
		mlx_put_pixel(graphics->image, col_index, y++, style->ceiling_color);
	while (y < draw.col_start + draw.column_height && y < WINDOW_HEIGHT)
	{
		draw.tex_y = (int)draw.tex_pos & (style->texture[wall_dir]->height - 1);
		draw.tex_pos += draw.step;
		mlx_put_pixel(graphics->image, col_index, y,
			get_pixel(style->texture[wall_dir],
			(unsigned int)(style->texture[wall_dir]->width * draw.tex_y
			+ draw.tex_x) * 4));
		y++;
	}
	while (y < WINDOW_HEIGHT)
		mlx_put_pixel(graphics->image, col_index, y++, style->floor_color);
}

t_draw	get_tex_x(double angle, double radial, double dist, int wall_dir)
{
	t_draw	draw;
	double	wallx;

	if (wall_dir == NORTH || wall_dir == SOUTH)
		wallx = cos(angle) * (dist / cos(radial * RAD)) + get_player()->x_pos;
	else
		wallx = sin(angle) * (dist / cos(radial * RAD)) + get_player()->y_pos;
	wallx -= floor(wallx);
	draw.tex_x = wallx * (double)get_style()->texture[wall_dir]->width;
	return (draw);
}

unsigned int	get_pixel(mlx_texture_t *tex, unsigned int pos)
{
	return (tex->pixels[pos] << 24 | tex->pixels[pos + 1] << 16 | tex->pixels[pos + 2] << 8 | 0xff);
}
