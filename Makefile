NAME		:= cub3D
CC			:= cc
MLXFLAGS	:= -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" # MacOS
#MLXFLAGS	:= -Iinclude -ldl -lglfw -pthread -lm # Linux
CFLAGS		:= -Wall -Wextra -Werror -O3  #-g -fsanitize=address -static-libsan
MLX_DIR		:= ./MLX42
LIBFT_DIR	:= ./libft
OBJ_DIR		:= obj/

HEADERS	:= -I ./include -I $(MLX_DIR)/include -I $(LIBFT)/include
MLX42	:= $(MLX_DIR)/build/libmlx42.a
LIBFT	:= $(LIBFT_DIR)/libft.a
SRCS	:= 	cub3d.c \
			cast_ray.c \
			ray_collision.c \
			ray_utils.c \
			errors.c \
			frees.c \
			game_state.c \
			gnl_chk.c \
			door_operation.c \
			minimap.c \
			move_collisions.c \
			move_enemies.c \
			move_mouse.c \
			move_player.c \
			move_player_vertical.c \
			parse.c \
			parse_map.c \
			parse_map_validate.c \
			parse_utils.c \
			render_ceiling.c \
			render_doors.c \
			render_enemies.c \
			render_floor.c \
			render_utils.c \
			render_walls.c \
			tokenize.c \
			weapons.c \
			init_game.c \
			init_textures.c \
			init_math_tables.c \
			load_textures.c \
			load_weapon_textures.c \
			enemy_textures.c \
			delete_textures.c \
			init_texture_utils.c \
			
OBJS	:= $(addprefix $(OBJ_DIR), ${SRCS:.c=.o})

all: $(NAME)

$(MLX42):
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(OBJS) $(MLX42)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42) $(MLXFLAGS) $(HEADERS) -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(MLX_DIR)/build

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re