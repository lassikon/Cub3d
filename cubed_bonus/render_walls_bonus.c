/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/30 11:07:52 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_wall(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int	row;

	row = 0;
	ray->ty = 0;
	ray->ty_step = (float)img->height / ray->height;
	if (game->render.top_wall < 0)
	{
		ray->ty += -game->render.top_wall * ray->ty_step;
		game->render.top_wall = 0;
		ray->height = SCREEN_HEIGHT;
	}
	get_brightness_lvl(game, ray);
	ray->tx = (float)(img->width / TILE_SIZE) * ray->col;
	ray->tx = fmod(ray->tx, img->width);
	ray->ty = fmod(ray->ty, img->height);
	while (row < ray->height)
	{
		if (game->render.top_wall + ray->height > SCREEN_HEIGHT)
			ray->height = SCREEN_HEIGHT - game->render.top_wall;
		put_texture_pixel(game, ray, img, game->render.top_wall + row);
		row++;
		ray->ty += ray->ty_step;
		if (ray->ty >= img->height)
			break ;
	}
}

static void	render_column(t_game *game, t_ray *ray)
{
	mlx_image_t	*img;
	float		ratio;
	int			fishtable;

	img = NULL;
	fishtable = (int)(fabs(game->p.angle - ray->angle) * game->math.fish_it);
	ray->distance *= game->math.fishcos[fishtable];
	ratio = game->dist_to_proj_plane / ray->distance;
	game->render.bottom_wall = (ratio * game->p.height) + game->vertical_center;
	ray->height = (game->dist_to_proj_plane * WALL_HEIGHT) / ray->distance;
	game->render.top_wall = game->render.bottom_wall - (int)ray->height;
	if (ray->door == 1)
		img = game->door_img;
	else if (ray->wall_side == NORTH && ray->door == 0)
		img = game->north_img;
	else if (ray->wall_side == SOUTH && ray->door == 0)
		img = game->south_img;
	else if (ray->wall_side == EAST && ray->door == 0)
		img = game->east_img;
	else if (ray->wall_side == WEST && ray->door == 0)
		img = game->west_img;
	draw_wall(game, ray, img);
	draw_floor(game, ray, game->floor_img);
	draw_ceiling(game, ray, game->ceiling_img);
}

void	render_walls(t_game *game)
{
	t_ray	ray;
	float	angle_step;

	ray.column = 0;
	angle_step = FOV / SCREEN_WIDTH;
	ray.angle = game->p.angle - FOV / 2;
	if (!game->floor_img)
		render_floor_color(game);
	if (!game->ceiling_img)
		render_ceiling_color(game);
	while (ray.column < SCREEN_WIDTH)
	{
		if (ray.angle < 0)
			ray.angle += 2 * PI;
		else if (ray.angle > 2 * PI)
			ray.angle -= 2 * PI;
		cast_ray(game, &ray);
		if (ray.distance < MAX_DEPTH)
			render_column(game, &ray);
		game->rays[ray.column] = ray;
		ray.column++;
		ray.angle += angle_step;
	}
}
