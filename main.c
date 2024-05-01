/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:32:54 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/01 16:31:52 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

# include "libft/include/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define TILE_SIZE 64
#define FOV (M_PI / 4) // Field of view (45 degrees)
#define RAY_COUNT SCREEN_WIDTH // Number of rays to cast

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 64
#define FOV (M_PI / 4) // Field of view (45 degrees)
#define MOVEMENT_SPEED 3.0f // Speed of player movement
#define STRAFE_SPEED 1.0f // Speed of player strafing
#define ROTATION_SPEED (M_PI / 120) // Speed of player rotation

// Simple 2D map (1 is a wall, 0 is floor)
const int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
};

typedef struct  player_s{
    float x; // Player's x-coordinate
    float y; // Player's y-coordinate
    float angle; // Player's viewing angle in radians
} player_t;

// Game structure to hold the MLX context, image, player, etc.
typedef struct s_game {
    mlx_t *mlx; // MLX42 context
    mlx_image_t *image; // The image used for rendering
    player_t player; // The player structure
} t_game;


// Ray structure
typedef struct {
    float x; // Ray's x position
    float y; // Ray's y position
    float distance; // Distance to the wall
} ray_t;

// Function to cast a ray and return the distance to the first wall
float cast_ray(player_t *player, float ray_angle) {
    float x = player->x;
    float y = player->y;

    float ray_x = cos(ray_angle); // Ray direction x-component
    float ray_y = sin(ray_angle); // Ray direction y-component

    while (1) { // Move along the ray until a wall is hit
        x += ray_x * 0.1f; // Increment the position along the ray
        y += ray_y * 0.1f;

        int map_x = (int)(x / TILE_SIZE); // Map coordinate x
        int map_y = (int)(y / TILE_SIZE); // Map coordinate y

        // If the ray hits a wall, return the distance
        if (map[map_y][map_x] == 1) {
            return sqrt((player->x - x) * (player->x - x) + (player->y - y) * (player->y - y));
        }
    }
}

// Function to render the walls using the raycasting algorithm
void render_walls(mlx_image_t *image, player_t *player) {
    for (int i = 0; i < RAY_COUNT; i++) {
        float ray_angle = (player->angle - FOV / 2) + ((float)i / (float)RAY_COUNT) * FOV; // Calculate the ray angle
        float distance = cast_ray(player, ray_angle); // Cast the ray

        int line_height = (int)(TILE_SIZE * SCREEN_HEIGHT / distance); // Height of the wall
        int line_start = (SCREEN_HEIGHT / 2) - (line_height / 2); // Start of the wall line

        if (line_start < 0) {
            line_start = 0; // Ensure the start is within bounds
        }
        if (line_height > SCREEN_HEIGHT) {
            line_height = SCREEN_HEIGHT; // Ensure the height is within bounds
        }

        // Draw the wall (vertical line)
        for (int y = line_start; y < line_start + line_height; y++) {
            int pixel_index = (y * SCREEN_WIDTH + i) * 4; // Calculate the pixel index

            image->pixels[pixel_index] = 255; // Red
            image->pixels[pixel_index + 1] = 255; // Green
            image->pixels[pixel_index + 2] = 255; // Blue
            image->pixels[pixel_index + 3] = 255; // Alpha
        }
    }
}


// Function to check if the player collides with a wall
int check_collision(float new_x, float new_y) {
    int map_x = (int)(new_x / TILE_SIZE); // Map x-coordinate
    int map_y = (int)(new_y / TILE_SIZE); // Map y-coordinate

    return (map[map_y][map_x] == 1); // Return true if there's a wall
}

// Function to handle player movement based on key input
void move_player(t_game *game) {
    player_t *player = &game->player;

	// Close window
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);

    // Forward movement
    if (mlx_is_key_down(game->mlx, MLX_KEY_W)) {
        float new_x = player->x + cos(player->angle) * MOVEMENT_SPEED;
        float new_y = player->y + sin(player->angle) * MOVEMENT_SPEED;
        
        // Check for collisions
        if (!check_collision(new_x, new_y)) {
            player->x = new_x;
            player->y = new_y;
        }
    }

    // Backward movement
    if (mlx_is_key_down(game->mlx, MLX_KEY_S)) {
        float new_x = player->x - cos(player->angle) * MOVEMENT_SPEED;
        float new_y = player->y - sin(player->angle) * MOVEMENT_SPEED;

        // Check for collisions
        if (!check_collision(new_x, new_y)) {
            player->x = new_x;
            player->y = new_y;
        }
    }

	// Strafe left
	if (mlx_is_key_down(game->mlx, MLX_KEY_A)) {
		float new_x = player->x - cos(player->angle + M_PI / 2) * STRAFE_SPEED;
		float new_y = player->y - sin(player->angle + M_PI / 2) * STRAFE_SPEED;

		// Check for collisions
		if (!check_collision(new_x, new_y)) {
			player->x = new_x;
			player->y = new_y;
		}
	}

	// Strafe right
	if (mlx_is_key_down(game->mlx, MLX_KEY_D)) {
		float new_x = player->x + cos(player->angle + M_PI / 2) * STRAFE_SPEED;
		float new_y = player->y + sin(player->angle + M_PI / 2) * STRAFE_SPEED;

		// Check for collisions
		if (!check_collision(new_x, new_y)) {
			player->x = new_x;
			player->y = new_y;
		}
	}

    // Rotate left
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
        player->angle -= ROTATION_SPEED;
		if (player->angle < 0)
			player->angle += 2 * M_PI;
    }

    // Rotate right
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
        player->angle += ROTATION_SPEED;
		if (player->angle > 2 * M_PI)
			player->angle -= 2 * M_PI;
    }
}

// Loop hook to handle player movement and render the raycasting view
void render_loop(void *param) {
    t_game *game = (t_game *)param;

    // Clear the image
    memset(game->image->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

    // Handle player movement
    move_player(game);

    // Render the walls using raycasting
    render_walls(game->image, &game->player);
}

// Main function
int main(void) {
    // Initialize MLX42
    mlx_t *mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster", false);
    if (!mlx) {
        fprintf(stderr, "Failed to initialize MLX42.\n");
        return EXIT_FAILURE;
    }

    // Create the rendering image
    mlx_image_t *image = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!image) {
        fprintf(stderr, "Failed to create MLX42 image.\n");
        return EXIT_FAILURE;
    }

    // Add the image to the window
    if (mlx_image_to_window(mlx, image, 0, 0) < 0) {
        fprintf(stderr, "Failed to add image to window.\n");
        return EXIT_FAILURE;
    }

    // Initialize the game context
    t_game game;
    game.mlx = mlx;
    game.image = image;

    // Initialize the player
    game.player.x = TILE_SIZE * 1.5f; // Starting x-coordinate
    game.player.y = TILE_SIZE * 1.5f; // Starting y-coordinate
    game.player.angle = 0.0f; // Default angle (facing right)

    // Set the loop hook for handling player movement and rendering
    mlx_loop_hook(game.mlx, render_loop, &game); // Pass the game context

    // Start the MLX42 loop
    mlx_loop(game.mlx); // Begin the event loop

	// Cleanup
	mlx_terminate(mlx);

    return 0;
}