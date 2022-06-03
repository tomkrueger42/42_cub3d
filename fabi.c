int	ft_fround(int mul, double num)
{
	double	f;

	f = (double)mul;
	f = f * num;
	if (f - (int)f > 0.5 && (int)(f + 1) < num)
		return ((int)(f + 1));
	return ((int)f);
}

static mlx_texture_t	*get_correct_tex(t_data *game, char wtype)
{
	if (wtype == 'N')
		return (game->imgs.tex_n);
	if (wtype == 'S')
		return (game->imgs.tex_s);
	if (wtype == 'E')
		return (game->imgs.tex_e);
	if (wtype == 'W')
		return (game->imgs.tex_w);
	return (0);
}

/*
	//color = create_trgb(255 * x_rat, 255 * y_rat, 255);
	//printf("color=%hhx\n", color);
	//printf("height=%d\n", tex->height);
	//printf("width=%d\n", tex->width);
	//printf("x=%d\n", pixel_pos.x);
	//printf("y=%d\n", pixel_pos.y);
	//color = *((u_int32_t *)pixel_reader);
*/
static uint32_t	get_texpixel(t_data *game, char wtype, double xrat, double yrat)
{
	mlx_texture_t	*tex;
	t_intpair		pixel_pos;
	uint32_t		color;
	uint8_t			*pixel_reader;

	tex = get_correct_tex(game, wtype);
	pixel_pos.x = ft_fround(tex->width, xrat);
	pixel_pos.y = ft_fround(tex->height, yrat);
	pixel_reader = tex->pixels;
	pixel_reader += (pixel_pos.y * tex->width) * tex->bytes_per_pixel;
	pixel_reader += pixel_pos.x * tex->bytes_per_pixel;
	color = create_trgb
		(*(pixel_reader + 0), *(pixel_reader + 1), *(pixel_reader + 2));
	return (color);
}

static uint32_t	get_pixel(t_data *game, int x, int y)
{
	int		h;
	int		fac;
	double	x_rat;
	double	y_rat;

	h = game->wall_heights[x];
	fac = 0.5 * (game->screen_height - h);
	if (y > fac && y < fac + h)
	{
		y_rat = (double)(y - fac) / h;
		x_rat = game->wall_shade[x];
		return (get_texpixel(game, game->wall_types[x], x_rat, y_rat));
	}
	else if (y > game->screen_height * 0.5)
		return (game->map.f_colour);
	else
		return (game->map.c_colour);
}

int	render_world(t_data *game)
{
	int			x;
	int			y;
	uint32_t	color;

	x = -1;
	while (++x < game->screen_width)
	{
		y = -1;
		while (++y < game->screen_height)
		{
			color = get_pixel(game, x, y);
			color = color << 8;
			mlx_put_pixel(game->main_img, x, y, 0xFF + color);
		}
	}
	return (1);
}