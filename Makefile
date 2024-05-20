NAME		:= cub3D
CC			:= cc
MLXFLAGS	:= -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" # MacOS
#MLXFLAGS	:= -Iinclude -ldl -lglfw -pthread -lm # Linux
CFLAGS		:= -Wall -Wextra -Werror -O3  -g -fsanitize=address
MLX_DIR		:= ./MLX42
LIBFT_DIR	:= ./libft
OBJ_DIR		:= obj/

HEADERS	:= -I ./include -I $(MLX_DIR)/include -I $(LIBFT)/include
MLX42	:= $(MLX_DIR)/build/libmlx42.a
LIBFT	:= $(LIBFT_DIR)/libft.a
SRCS	:= 	cub3d.c \
			move_player.c \
			move_player_vertical.c \
			render_walls.c \
			gnl_chk.c \
			parse.c \
			parse_map.c \
			parse_map_validate.c \
			parse_utils.c \
			tokenize.c \
			errors.c \
			frees.c \
			minimap.c \
			cast_ray.c \
			move_mouse.c \
			operate_door.c
			
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