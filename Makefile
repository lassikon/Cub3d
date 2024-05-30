NAME		:= cub3D
BNS_NAME	:= cub3D_bonus
CC			:= cc
MLXFLAGS	:= -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" # MacOS
#MLXFLAGS	:= -Iinclude -ldl -lglfw -pthread -lm # Linux
CFLAGS		:= -Wall -Wextra -Werror -O3  #-g -fsanitize=address -static-libsan
MLX_DIR		:= ./MLX42
LIBFT_DIR	:= ./libft
BNS_DIR		:= cubed_bonus/
BNS_OBJ_DIR	:= cubed_bonus/obj/
MNDTRY_DIR		:= cubed_mandatory/
MNDTRY_OBJ_DIR	:= cubed_mandatory/obj/

HEADERS		:= -I ./include -I $(MLX_DIR)/include -I $(LIBFT)/include
MLX42		:= $(MLX_DIR)/build/libmlx42.a
LIBFT		:= $(LIBFT_DIR)/libft.a

MNDTRY_SRCS	:= 	cub3d.c \
			init_game.c \
			init_textures.c \
			move_player.c \
			gnl_chk.c \
			parse.c \
			parse_map.c \
			parse_map_validate.c \
			parse_utils.c \
			tokenize.c \
			errors.c \
			frees.c \
			cast_ray.c \
			render_walls.c \
			render.c

MNDTRY_OBJS	:= $(addprefix $(MNDTRY_OBJ_DIR), ${MNDTRY_SRCS:.c=.o})

BNS_SRCS	:= 	cub3d_bonus.c \
			cast_ray_bonus.c \
			ray_collision_bonus.c \
			ray_utils_bonus.c \
			errors_bonus.c \
			frees_bonus.c \
			game_state_bonus.c \
			gnl_chk_bonus.c \
			door_operation_bonus.c \
			minimap_bonus.c \
			move_collisions_bonus.c \
			move_enemies_bonus.c \
			move_mouse_bonus.c \
			move_player_bonus.c \
			move_player_vertical_bonus.c \
			parse_bonus.c \
			parse_map_bonus.c \
			parse_map_validate_bonus.c \
			parse_utils_bonus.c \
			render_ceiling_bonus.c \
			render_doors_bonus.c \
			render_enemies_bonus.c \
			render_floor_bonus.c \
			render_utils_bonus.c \
			render_walls_bonus.c \
			tokenize_bonus.c \
			weapons_bonus.c \
			init_game_bonus.c \
			init_textures_bonus.c \
			init_math_tables_bonus.c \
			load_textures_bonus.c \
			load_weapon_textures_bonus.c \
			enemy_textures_bonus.c \
			delete_textures_bonus.c \
			init_texture_utils_bonus.c \
			
BNS_OBJS	:= $(addprefix $(BNS_OBJ_DIR), ${BNS_SRCS:.c=.o})

all: $(NAME)

$(MLX42):
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(LIBFT):
	@make -C $(LIBFT_DIR)

#mandatory
$(MNDTRY_OBJ_DIR)%.o: $(MNDTRY_DIR)%.c
	@mkdir -p $(MNDTRY_OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

#bonus
$(BNS_OBJ_DIR)%.o: $(BNS_DIR)%.c
	@mkdir -p $(BNS_OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(MNDTRY_OBJS) $(MLX42)
	@$(CC) $(CFLAGS) $(MNDTRY_OBJS) $(LIBFT) $(MLX42) $(MLXFLAGS) $(HEADERS) -o $(NAME)

bonus: .bonus

.bonus: $(LIBFT) $(BNS_OBJS) $(MLX42)
	@touch $@
	@$(CC) $(CFLAGS) $(BNS_OBJS) $(LIBFT) $(MLX42) $(MLXFLAGS) $(HEADERS) -o $(BNS_NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(MNDTRY_OBJS)
	@rm -rf $(MNDTRY_OBJ_DIR)
	@rm -rf $(BNS_OBJS)
	@rm -rf $(BNS_OBJ_DIR)
	@rm -rf $(MLX_DIR)/build
	@rm -f .bonus

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)
	@rm -rf $(BNS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus