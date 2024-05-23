/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/23 12:07:23 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int red, int green, int blue, int alpha)
{
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

void	put_texture_pixel(t_game *game, t_ray *ray, mlx_image_t *img, int row)
{
	int	color;
	int	red;
	int	green;
	int	blue;
	int	alpha;

	ray->pixel = &img->pixels[(int)ray->ty * img->width * 4 + (int)ray->tx * 4];
	if (ray->pixel[3] != 0)
	{
		red = ray->pixel[0] * game->render.brightness;
		green = ray->pixel[1] * game->render.brightness;
		blue = ray->pixel[2] * game->render.brightness;
		alpha = ray->pixel[3];
		color = get_rgba(red, green, blue, alpha);
		mlx_put_pixel(game->image, ray->column, row, color);
	}
}

void	get_brightness_lvl(t_game *game, t_ray *ray)
{
	if (ray->wall_side == EAST || ray->wall_side == WEST)
		game->render.brightness = 180 / ray->distance;
	else
		game->render.brightness = 130 / ray->distance;
	if (game->render.brightness > 1)
		game->render.brightness = 1;
	if (game->render.brightness < 0.1)
		game->render.brightness = 0.1;
}

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

void	draw_moving_door(t_game *game, t_ray *ray)
{
	int	row;

	row = 0;
	ray->ty = 0;
	ray->ty_step = (float)game->door_img->height / ray->height;
	if (game->render.top_wall < 0)
	{
		ray->ty += -game->render.top_wall * ray->ty_step;
		game->render.top_wall = 0;
		ray->height = SCREEN_HEIGHT;
	}
	ray->tx = (float)(game->door_img->width / TILE_SIZE) * (ray->door_col + 5 * ray->door_state);
	if (ray->tx >= game->door_img->width)
		return ;
	game->render.brightness = 1;
	ray->tx = fmod(ray->tx, game->door_img->width);
	ray->ty = fmod(ray->ty, game->door_img->height);
	while (row < ray->height)
	{
		put_texture_pixel(game, ray, game->door_img, game->render.top_wall + row);
		row++;
		ray->ty += ray->ty_step;
		if (ray->ty >= game->door_img->height)
			break ;
	}
}

void	render_moving_door(t_game *game, t_ray *ray)
{
	float		ratio;
	int			fishtable;

	fishtable = (int)(fabs(game->p.angle - ray->angle) * game->math.fish_it);
	ray->door_distance *= game->math.fishcos[fishtable];
	ratio = game->dist_to_proj_plane / ray->door_distance;
	game->render.bottom_wall = (ratio * game->p.height) + game->vertical_center;
	ray->height = (game->dist_to_proj_plane * WALL_HEIGHT) / ray->door_distance;
	game->render.top_wall = game->render.bottom_wall - (int)ray->height;
	draw_moving_door(game, ray);
}

void	moving_door(t_game *game)
{
	int	i;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		if (game->rays[i].door_state)
		{
			if (game->rays[i].door_distance < game->rays[i].distance)
				render_moving_door(game, &game->rays[i]);
		}
		i++;
	}
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
