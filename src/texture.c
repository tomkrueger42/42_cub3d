#include "cub3d.h"
#include <math.h>

unsigned int	get_pixel(mlx_texture_t *tex, unsigned int pos);

void	draw_tex(int col_index, t_draw draw, int wall_dir)
{
	int			y;
	t_style		*style;
	t_graphics	*graphics;

	y = 0;
	style = get_style();
	graphics = get_graphics();
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

t_draw	set_vars(double angle, double radial, double dist, int wall_dir)
{
	t_draw	draw;
	double	wallx;
	t_style	*style;

	style = get_style();
	if (wall_dir == NORTH || wall_dir == SOUTH)
		wallx = cos(angle) * (dist / cos(radial * RAD)) + get_player()->x_pos;
	else
		wallx = sin(angle) * (dist / cos(radial * RAD)) + get_player()->y_pos;
	wallx -= floor(wallx);
	draw.tex_x = wallx * (double)style->texture[wall_dir]->width;
	draw.column_height = 1.0 / dist * WINDOW_HEIGHT;
	draw.step = (double)style->texture[wall_dir]->height / draw.column_height;
	draw.col_start = (WINDOW_HEIGHT - draw.column_height) / 2;
	if (draw.column_height > WINDOW_HEIGHT)
		draw.tex_pos = (draw.column_height - WINDOW_HEIGHT) / 2 * draw.step;
	else
		draw.tex_pos = draw.step;
	return (draw);
}

unsigned int	get_pixel(mlx_texture_t *tex, unsigned int pos)
{
	return (tex->pixels[pos] << 24 | tex->pixels[pos + 1] << 16
		| tex->pixels[pos + 2] << 8 | 0xff);
}
