/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/15 15:25:11 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    render_ceiling(t_game *game)
{
    int    x;
    int    y;
    int    color;

    y = 0;
  
    while (y <= game->vertical_center)
    {
        x = 0;
		color = get_rgba(game->ceiling_color[0], game->ceiling_color[1],
            game->ceiling_color[2], 255);
        while (x < SCREEN_WIDTH)
        {
            mlx_put_pixel(game->image, x, y, color);
            x++;
        }
        y++;
    }
}

void    render_floor(t_game *game)
{
    int    x;
    int    y;
    int    color;

    y = SCREEN_HEIGHT - 1;
    while (y > game->vertical_center)
    {
		float b = (y - game->vertical_center) / (float)game->vertical_center;
		if (b < 0)
			b = 0;
   		color = get_rgba(game->floor_color[0]*b, game->floor_color[1]*b,
        	game->floor_color[2]*b, 255);
        x = 0;
        while (x < SCREEN_WIDTH)
        {
            mlx_put_pixel(game->image, x, y, color);
            x++;
        }
        y--;
    }
}

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

void	get_wall_ray_x_y(t_game *game, t_ray *ray)
{
	if (ray->wall_side == EAST || ray->wall_side == WEST)
		game->render.brightness = 180 / ray->distance;
	else
		game->render.brightness = 130 / ray->distance;
	if (game->render.brightness > 1)
		game->render.brightness = 1;
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
	get_wall_ray_x_y(game, ray);
	ray->tx = (float)(img->width / TILE_SIZE) * ray->col;
	ray->tx = fmod(ray->tx, img->width);
	ray->ty = fmod(ray->ty, img->height);
	while (row < ray->height)
	{
		put_texture_pixel(game, ray, img, game->render.top_wall + row);
		row++;
		ray->ty += ray->ty_step;
		if (ray->ty >= img->height)
			break ;
	}
}

void	get_floor_ray_x_y(t_game *game, t_ray *ray, int row)
{
	float	eye_to_floor;
	float	ratio;
	float	angle;
	int		fishtable;
	int		trigtable;

	ratio = game->p.height / (row - game->vertical_center);
	fishtable = (int)(fabs(game->p.angle - ray->angle) * game->math.fish_it);
	trigtable = (int)(ray->angle * game->math.trig_it);
	angle = game->math.ifishcos[fishtable];
	eye_to_floor = ratio * game->dist_to_proj_plane * angle;
	ray->tx = game->p.x + game->math.cos[trigtable] * eye_to_floor;
	ray->ty = game->p.y + game->math.sin[trigtable] * eye_to_floor;
	game->render.brightness = 150 / eye_to_floor;
	if (game->render.brightness > 1)
		game->render.brightness = 1;
}

/*draw floors*/
void	draw_floor(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int		row;

	if (!img)
		return ;
	row = (int)game->render.bottom_wall;
	while (row < SCREEN_HEIGHT)
	{
		get_floor_ray_x_y(game, ray, row);
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
		put_texture_pixel(game, ray, img, row);
		row++;
	}
}

void	get_ceiling_ray_x_y(t_game *game, t_ray *ray, int row)
{
	float	eye_to_floor;
	float	ratio;
	float	angle;
	int		fishtable;
	int		trigtable;

	ratio = (WALL_HEIGHT - game->p.height) / (game->vertical_center - row);
	fishtable = (int)(fabs(game->p.angle - ray->angle) * game->math.fish_it);
	trigtable = (int)(ray->angle * game->math.trig_it);
	angle = game->math.ifishcos[fishtable];
	eye_to_floor = ratio * game->dist_to_proj_plane * angle;
	ray->tx = game->p.x + game->math.cos[trigtable] * eye_to_floor;
	ray->ty = game->p.y + game->math.sin[trigtable] * eye_to_floor;
	game->render.brightness = 100 / eye_to_floor;
	if (game->render.brightness > 1)
		game->render.brightness = 1;
}

/*draw ceiling*/
void	draw_ceiling(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int		row;

	if (!img)
		return ;
	row = (int)game->render.top_wall;
	while (row >= 0)
	{
		get_ceiling_ray_x_y(game, ray, row);
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
		put_texture_pixel(game, ray, img, row);
		row--;
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
		render_floor(game);
	if (!game->ceiling_img)
		render_ceiling(game);
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
