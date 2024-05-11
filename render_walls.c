/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/11 10:46:24 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_rgba(int red, int green, int blue, int alpha)
{
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

static float	fishbowl(float ray_angle, float player_angle)
{
	float	angle;

	angle = player_angle - ray_angle;
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (cos(angle));
}

static void	draw_column(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int		y;
	int		color;

	y = 0;
	ray->ty_step = (float)img->height / ray->height;
	ray->ty = 0;
	if (game->render.top_wall < 0)
	{
		ray->ty += -game->render.top_wall * ray->ty_step;
		game->render.top_wall = 0;
	}
	ray->tx = (float)(img->width / TILE_SIZE) * ray->col;
/* 	ray->tx = ((int)ray->tx % img->width);
	ray->ty = ((int)ray->ty % img->height); */
	while (y < ray->height)
	{
		ray->pixel = &img->pixels[(int)ray->ty * img->width * 4 + (int)ray->tx * 4];
		if (ray->pixel[3] != 0)
		{
			color = get_rgba(ray->pixel[0], ray->pixel[1], ray->pixel[2], ray->pixel[3]);
			mlx_put_pixel(game->image, ray->column, game->render.top_wall + y, color);
		}
		y++;
		ray->ty += ray->ty_step;
		if (ray->ty >= img->height)
			break ;
	}
	/*draw floors*/
	y = (int)game->render.bottom_wall;
	while (y < SCREEN_HEIGHT)
	{
		float fy = y - game->vertical_center;
		if (fy != 0)
		{
			float ratio = game->p.height / fy;
			ray->tx = game->p.x  + cos(ray->angle)*ratio*game->dist_to_proj_plane/fishbowl(ray->angle, game->p.angle);
			ray->ty = game->p.y + sin(ray->angle)*ratio*game->dist_to_proj_plane/fishbowl(ray->angle, game->p.angle);
			//ray->tx = fmod(ray->tx, TILE_SIZE); // Wrap texture coordinates around the tile size
			//ray->ty = fmod(ray->ty, TILE_SIZE);
			if (ray->tx < 0)
				ray->tx += TILE_SIZE; // Ensure positive texture coordinates
			if (ray->ty < 0)
				ray->ty += TILE_SIZE;
			ray->tx = ray->tx - (int)(ray->tx / TILE_SIZE) * TILE_SIZE;
			ray->ty = ray->ty - (int)(ray->ty / TILE_SIZE) * TILE_SIZE;
			ray->tx = (float)img->width / TILE_SIZE * ray->tx;
			ray->ty = (float)img->height / TILE_SIZE * ray->ty;
			ray->tx = ((int)ray->tx % img->width);
			ray->ty = ((int)ray->ty % img->height);
			ray->pixel = &img->pixels[(int)ray->ty * img->width * 4 + (int)ray->tx * 4];
			if (ray->pixel[3] != 0)
			{
				color = get_rgba(ray->pixel[0], ray->pixel[1], ray->pixel[2], ray->pixel[3]);
				mlx_put_pixel(game->image, ray->column, y, color);
			}
			y++;
		}
	}
	/*draw ceiling*/
	y = (int)game->render.top_wall;
	while (y >= 0)
	{
		float ratio = (WALL_HEIGHT - game->p.height) / (game->vertical_center - y);
		ray->tx = game->p.x  + cos(ray->angle)*ratio*game->dist_to_proj_plane/fishbowl(ray->angle, game->p.angle);
		ray->ty = game->p.y + sin(ray->angle)*ratio*game->dist_to_proj_plane/fishbowl(ray->angle, game->p.angle);
 		//ray->tx = fmod(ray->tx, TILE_SIZE); // Wrap texture coordinates around the tile size
		//ray->ty = fmod(ray->ty, TILE_SIZE); 
		if (ray->tx < 0)
			ray->tx += TILE_SIZE; // Ensure positive texture coordinates
		if (ray->ty < 0)
			ray->ty += TILE_SIZE;
		ray->tx = ray->tx - (int)(ray->tx / TILE_SIZE) * TILE_SIZE;
		ray->ty = ray->ty - (int)(ray->ty / TILE_SIZE) * TILE_SIZE;
		ray->tx = (float)img->width / TILE_SIZE * ray->tx;
		ray->ty = (float)img->height / TILE_SIZE * ray->ty;
		ray->tx = ((int)ray->tx % img->width);
		ray->ty = ((int)ray->ty % img->height);
		ray->pixel = &img->pixels[(int)ray->ty * img->width * 4 + (int)ray->tx * 4];
		if (ray->pixel[3] != 0)
		{
			color = get_rgba(ray->pixel[0], ray->pixel[1], ray->pixel[2], ray->pixel[3]);
			mlx_put_pixel(game->image, ray->column, y, color);
		}
		y--;
	}
}

static void	render_column(t_game *game, t_ray *ray)
{
	ray->distance *= fishbowl(ray->angle, game->p.angle);
	float ratio = game->dist_to_proj_plane / ray->distance;
	game->render.bottom_wall = (ratio * game->p.height) + game->vertical_center;
	ray->height = (game->dist_to_proj_plane * WALL_HEIGHT) / ray->distance;
	game->render.top_wall = game->render.bottom_wall - (int)ray->height;
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
