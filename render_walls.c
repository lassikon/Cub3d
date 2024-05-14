/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/14 15:13:08 by jberay           ###   ########.fr       */
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

/* brightness level
	E|W = 180
	N|S = 130
	FL = 150
	CL = 100 */

static void	draw_wall(t_game *game, t_ray *ray, mlx_image_t *img)
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
		ray->height = SCREEN_HEIGHT;
	}
	ray->tx = (float)(img->width / TILE_SIZE) * ray->col;
	ray->tx = fmod(ray->tx, img->width);
	ray->ty = fmod(ray->ty, img->height);
	if (ray->wall_side == EAST || ray->wall_side == WEST)
		game->render.brightness = 180 / ray->distance;
	else
		game->render.brightness = 130 / ray->distance;
	if (game->render.brightness > 1)
		game->render.brightness = 1;
	while (y < ray->height)
	{
		ray->pixel = &img->pixels[(int)ray->ty * img->width * 4 + (int)ray->tx * 4];
		if (ray->pixel[3] != 0)
		{
			color = get_rgba(ray->pixel[0]*game->render.brightness, ray->pixel[1]*game->render.brightness, ray->pixel[2]*game->render.brightness, ray->pixel[3]);
			mlx_put_pixel(game->image, ray->column, game->render.top_wall + y, color);
		}
		y++;
		ray->ty += ray->ty_step;
		if (ray->ty >= img->height)
			break ;
	}


}

/*draw floors*/
static void	draw_floor(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int	row;
	int	color;

	row = (int)game->render.bottom_wall;
	while (row < SCREEN_HEIGHT)
	{
		float ratio = game->p.height / (row - game->vertical_center);
		ray->tx = game->p.x  + cos(ray->angle)*ratio*game->dist_to_proj_plane/fishbowl(ray->angle, game->p.angle);
		ray->ty = game->p.y + sin(ray->angle)*ratio*game->dist_to_proj_plane/fishbowl(ray->angle, game->p.angle);
		game->render.brightness = 150 / (ratio*game->dist_to_proj_plane/fishbowl(ray->angle, game->p.angle));
		if (game->render.brightness > 1)
			game->render.brightness = 1;
		if (ray->tx < 0)
			ray->tx += TILE_SIZE;
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
			color = get_rgba(ray->pixel[0]*game->render.brightness, ray->pixel[1]*game->render.brightness, ray->pixel[2]*game->render.brightness, ray->pixel[3]);
			mlx_put_pixel(game->image, ray->column, row, color);
		}
		row++;
	}
}

/*draw ceiling*/
static void	draw_ceiling(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int	row;
	int	color;

	row = (int)game->render.top_wall;
	while (row >= 0)
	{
		float ratio = (WALL_HEIGHT - game->p.height) / (game->vertical_center - row);
		ray->tx = game->p.x  + cos(ray->angle)*ratio*game->dist_to_proj_plane/fishbowl(ray->angle, game->p.angle);
		ray->ty = game->p.y + sin(ray->angle)*ratio*game->dist_to_proj_plane/fishbowl(ray->angle, game->p.angle);
		game->render.brightness = 100 / (ratio*game->dist_to_proj_plane/fishbowl(ray->angle, game->p.angle));
		if (game->render.brightness > 1)
			game->render.brightness = 1;
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
			color = get_rgba(ray->pixel[0]*game->render.brightness, ray->pixel[1]*game->render.brightness, ray->pixel[2]*game->render.brightness, ray->pixel[3]);
			mlx_put_pixel(game->image, ray->column, row, color);
		}
		row--;
	}
}

static void	render_column(t_game *game, t_ray *ray)
{
	mlx_image_t	*img;

	img = NULL;
	ray->distance *= fishbowl(ray->angle, game->p.angle);
	float ratio = game->dist_to_proj_plane / ray->distance;
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
