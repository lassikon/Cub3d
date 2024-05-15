/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/15 14:05:54 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_rgba(int red, int green, int blue, int alpha)
{
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

static float	fishbowl(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (cos(angle));
}

static void	draw_column(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int	y;
	int	color;

	ray->ty_step = (float)IMG_HEIGHT / ray->height;
	ray->ty = 0;
	if (ray->height > SCREEN_HEIGHT)
	{
		ray->ty += (ray->height - SCREEN_HEIGHT) / 2 * ray->ty_step;
		ray->height = SCREEN_HEIGHT;
	}
	y = game->vertical_center - ray->height / 2;
	ray->tx = (int)(ray->col * (float)(IMG_WIDTH / TILE)) * 4;
	while (y < game->vertical_center + ray->height / 2 && y < SCREEN_HEIGHT)
	{
		ray->pix = &img->pixels[(int)ray->ty * IMG_WIDTH * 4 + ray->tx];
		if (!ray->pix[3])
			break ;
		color = get_rgba(ray->pix[0], ray->pix[1], ray->pix[2], ray->pix[3]);
		mlx_put_pixel(game->image, ray->column, y, color);
		y++;
		ray->ty += ray->ty_step;
		if (ray->ty >= IMG_HEIGHT)
			break ;
	}
}

void	render_ceiling(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	color = get_rgba(game->ceiling_color[0], game->ceiling_color[1],
			game->ceiling_color[2], 255);
	while (y <= game->vertical_center)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(game->image, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_floor(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = game->vertical_center;
	color = get_rgba(game->floor_color[0], game->floor_color[1],
			game->floor_color[2], 255);
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(game->image, x, y, color);
			x++;
		}
		y++;
	}
}

static void	render_column(t_game *game, t_ray *ray)
{
	ray->distance *= fishbowl(game->p.angle - ray->angle);
	ray->height = (int)(TILE / ray->distance * game->dist_to_proj_plane);
	if (ray->wall_side == NORTH)
		draw_column(game, ray, game->north_img);
	else if (ray->wall_side == SOUTH)
		draw_column(game, ray, game->south_img);
	else if (ray->wall_side == EAST)
		draw_column(game, ray, game->east_img);
	else if (ray->wall_side == WEST)
		draw_column(game, ray, game->west_img);
}

void	render_walls(t_game *game)
{
	t_ray	ray;
	float	angle_step;

	ray.column = 0;
	angle_step = FOV / SCREEN_WIDTH;
	ray.angle = game->p.angle - FOV / 2;
	render_ceiling(game);
	render_floor(game);
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
