/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/09 13:10:38 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_rgba(int red, int green, int blue, int alpha)
{
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

static void	fishbowl_correction(t_ray *ray, float player_angle)
{
	float	angle;

	angle = player_angle - ray->angle;
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	ray->distance *= cos(angle);
}

static void	draw_column(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int		y;
	int		color;

	ray->ty_step = (float)img->height / ray->height;
	ray->ty = 0;
	if (ray->height > SCREEN_HEIGHT)
	{
		ray->ty += (ray->height - SCREEN_HEIGHT) / 2 * ray->ty_step;
		ray->height = SCREEN_HEIGHT;
	}
	y = game->vertical_center - ray->height / 2;
	if (y < 0)
	{
		ray->ty += -y * ray->ty_step;
		y = 0;
	}
	ray->tx = (float)(img->width / TILE_SIZE) * ray->col;
	while (y < game->vertical_center + ray->height / 2 && y < SCREEN_HEIGHT)
	{
		ray->pixel = &img->pixels[(int)ray->ty * img->width * 4 + (int)ray->tx * 4];
		if (ray->pixel[3] != 0)
		{
			color = get_rgba(ray->pixel[0], ray->pixel[1], ray->pixel[2], ray->pixel[3]);
			mlx_put_pixel(game->image, ray->column, y, color);
		}
		y++;
		ray->ty += ray->ty_step;
		if (ray->ty >= img->height)
			break ;
	}
}

static void	render_column(t_game *game, t_ray *ray)
{
	fishbowl_correction(ray, game->p.angle);
	ray->height = (int)(TILE_SIZE / ray->distance * game->dist_to_proj_plane);
	if (ray->wall_side == NORTH)
		draw_column(game, ray, game->north_img);
	if (ray->wall_side == SOUTH)
		draw_column(game, ray, game->south_img);
	if (ray->wall_side == EAST)
		draw_column(game, ray, game->east_img);
	if (ray->wall_side == WEST)
		draw_column(game, ray, game->west_img);
}

void	render_walls(t_game *game)
{
	t_ray	ray;
	float	angle_step;

	ray.column = 0;
	angle_step = FOV / SCREEN_WIDTH;
	ray.angle = game->p.angle - FOV / 2;
	while (ray.column < SCREEN_WIDTH)
	{
		if (ray.angle < 0)
			ray.angle += 2 * PI;
		else if (ray.angle > 2 * PI)
			ray.angle -= 2 * PI;
		cast_ray(game, &ray);
		if (ray.distance < MAX_DEPTH)
			render_column(game, &ray);
		ray.column++;
		ray.angle += angle_step;
	}
}
