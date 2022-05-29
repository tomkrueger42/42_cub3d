#include "cub3d.h"
#include <math.h>
#include <stdio.h>

t_ray	*ray(void)
{
	static t_ray	*ray;

	if (ray == NULL)
	{
		ray = ft_calloc(1, sizeof(t_ray));
		if (ray == NULL)
			put_error_and_exit("malloc failure in player()", 1);
	}
	return (ray);
}

// calc the len of first intersect with HORI within tile
int	first_intersect_hori(void)
{
	int	len;
	int adjacent;

	ray()->y_tile_play_pos = player()->y_pos - (int)player()->y_pos;

	if (player()->direction < PI)
	{
		ray()->y_intersect_pos = (int)player()->y_pos + 1;
		ray()->x_intersect_pos = player()->x_pos + ray()->y_tile_play_pos / tan(player()->direction);
	}
	else
	{
		ray()->y_intersect_pos = (int)player()->y_pos;
		ray()->x_intersect_pos = player()->x_pos - ray()->y_tile_play_pos / tan(player()->direction);
	}

	adjacent = (ray()->y_intersect_pos - ray()->y_tile_play_pos) / tan(player()->direction);
	len = (adjacent / cos(player()->direction));

	my_mlx_pixel_put(graphics(), ray()->x_intersect_pos * map()->tile_size - 1, ray()->y_intersect_pos * map()->tile_size, 0xFFFFFF);
	my_mlx_pixel_put(graphics(), ray()->x_intersect_pos * map()->tile_size, ray()->y_intersect_pos * map()->tile_size, 0xFF0000);
	my_mlx_pixel_put(graphics(), ray()->x_intersect_pos * map()->tile_size + 1, ray()->y_intersect_pos * map()->tile_size, 0xFFFFFF);
	
	return (len);
}

// calc the len (=hypothenuse) of first intersect with VERTI within tile
int	first_intersect_verti(void)
{
	int	opposite;
	int hypotenuse;

	ray()->x_tile_play_pos = player()->x_pos - (int)player()->x_pos;
	opposite = tan(player()->direction) * (map()->tile_size - ray()->x_tile_play_pos);

	if (player()->direction < 0.5 * PI || player()->direction > 1.5 * PI)
	{
		ray()->y_intersect_pos = player()->y_pos + ray()->x_tile_play_pos / cos(player()->direction) * sin(player()->direction);
		ray()->x_intersect_pos = (int)player()->x_pos + 1;
	}
	else
	{
		ray()->y_intersect_pos = player()->y_pos - ray()->x_tile_play_pos / cos(player()->direction) * sin(player()->direction);
		ray()->x_intersect_pos = (int)player()->x_pos;
	}

	hypotenuse = opposite / sin(player()->direction);

	
	my_mlx_pixel_put(graphics(), ray()->x_intersect_pos * map()->tile_size, ray()->y_intersect_pos * map()->tile_size - 1, 0xff0000);
	my_mlx_pixel_put(graphics(), ray()->x_intersect_pos * map()->tile_size, ray()->y_intersect_pos * map()->tile_size, 0xff0000);
	my_mlx_pixel_put(graphics(), ray()->x_intersect_pos * map()->tile_size, ray()->y_intersect_pos * map()->tile_size + 1, 0xff0000);
	
	return (hypotenuse);
}

// returns the length of first intersect within tile, depending on mode, either HORI or VERTI
int	len_first_intersect(int modus)
{
	int len;

	if (modus == HORI)
		len = first_intersect_hori();
	if (modus == VERTI)
		len = first_intersect_verti();
	return (len);
}


// if modus is HORI, func will add up xsteps until wall-hit else if VERTI func will add up ysteps
int	loop_step_till_wall(int modus)
{
	// int len_till_wall;
	int	len_intersect;
	int total_xstep;
	int total_ystep;

	len_intersect = len_first_intersect(modus);
	total_xstep = ray()->x_step;
	total_ystep = ray()->y_step;
	/* printf("x_inter: %d, x_step: %d\n", ray()->x_intersect_pos, total_xstep);
	printf("y_inter: %d, y_step: %d\n", ray()->y_intersect_pos, total_ystep); */
	// while(ray()->y_intersect_pos + total_ystep < map()->len * map()->tile_size && ray()->x_intersect_pos + total_xstep < map()->width * map()->tile_size)
	// {
	// 	len_till_wall = 0;
	// 	printf("x_inter: %d, x_step: %d\n", ray()->x_intersect_pos, total_xstep);
	// 	if (map()->data[ray()->y_intersect_pos + total_ystep][ray()->x_intersect_pos + total_xstep] == 1)
	// 	{
	// 		printf("inside if()\n");
	// 		printf("x: %d, y: %d\n", ray()->x_intersect_pos + total_xstep, ray()->y_intersect_pos + total_ystep);
	// 		// my_mlx_pixel_put(graphics(), ray()->x_intersect_pos + total_xstep - 1, ray()->y_intersect_pos + total_ystep - 1, 0xffffff);
	// 		// my_mlx_pixel_put(graphics(), ray()->x_intersect_pos + total_xstep, ray()->y_intersect_pos + total_ystep - 1, 0xffffff);
	// 		// my_mlx_pixel_put(graphics(), ray()->x_intersect_pos + total_xstep + 1, ray()->y_intersect_pos + total_ystep - 1, 0xffffff);
	// 		// my_mlx_pixel_put(graphics(), ray()->x_intersect_pos + total_xstep - 1, ray()->y_intersect_pos + total_ystep, 0xffffff);
	// 		// my_mlx_pixel_put(graphics(), ray()->x_intersect_pos + total_xstep, ray()->y_intersect_pos + total_ystep, 0xffffff);
	// 		// my_mlx_pixel_put(graphics(), ray()->x_intersect_pos + total_xstep + 1, ray()->y_intersect_pos + total_ystep, 0xffffff);
	// 		// my_mlx_pixel_put(graphics(), ray()->x_intersect_pos + total_xstep - 1, ray()->y_intersect_pos + total_ystep + 1, 0xffffff);
	// 		// my_mlx_pixel_put(graphics(), ray()->x_intersect_pos + total_xstep, ray()->y_intersect_pos + total_ystep + 1, 0xffffff);
	// 		// my_mlx_pixel_put(graphics(), ray()->x_intersect_pos + total_xstep + 1, ray()->y_intersect_pos + total_ystep + 1, 0xffffff);
	// 		if (modus == HORI)
	// 		{
	// 			len_till_wall = len_intersect + total_xstep;
	// 			break ;
	// 		}
	// 		if (modus == VERTI)
	// 		{
	// 			len_till_wall = len_intersect + total_ystep;
	// 			break ;
	// 		}
	// 	}
	// 	total_xstep += ray()->x_step;
	// 	total_ystep += ray()->y_step;
	// }
	return (/* len_till_wall */ 0);
}

// adds up first_intersect + (multiple) x/y-steps until it hits wall
int	len_hit_hori_or_verti(int modus)
{
	int	till_wall;

	till_wall = 0;

	if (modus == HORI)
	{
		ray()->y_step = map()->tile_size;
		ray()->x_step = ray()->y_step / tan(player()->direction);

		//
		// printf("tan() is %f\n", tan(player()->direction));
		// printf("player-dir  is %f\n", player()->direction);
		// printf("x_step is: %f, y_step is: %f\n", ray()->x_step, ray()->y_step);
		//

		till_wall = loop_step_till_wall(HORI);
	}
	if (modus == VERTI)
	{
		ray()->x_step = map()->tile_size;
		ray()->y_step = ray()->x_step / cos(player()->direction);

		//
		// printf("x_step is: %f, y_step is: %f\n", ray()->x_step, ray()->y_step);
		//
		till_wall = loop_step_till_wall(VERTI);
	}

	//
	// my_mlx_pixel_put(graphics(), ray()->x_tile_play_pos + till_wall, ray()->y_tile_play_pos + till_wall, 0xff0000);
	// my_mlx_pixel_put(graphics(), map()->tile_size * (ray()->x_tile_play_pos + till_wall), map()->tile_size * (ray()->y_tile_play_pos + till_wall), 0xff0000);
	//
	return (till_wall);
}

// decides which hit (hori or verti) is closer to player --> this will be the length of the ray hitting the wall
int	len_hit_wall(void)
{
	if (len_hit_hori_or_verti(HORI) < len_hit_hori_or_verti(VERTI))
		return(len_hit_hori_or_verti(HORI));
	else
		return(len_hit_hori_or_verti(VERTI));
}