NAME		:= cub3d
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g -fsanitize=address
MLXFLAGS	:= -Iinclude -lglfw -L"/Users/lkonttin/.brew/opt/glfw/lib/"
#MLXFLAGS	:= -Iinclude -ldl -lglfw -pthread -lm
CFLAGS		:= -Wall -Wextra -Werror -g -fsanitize=address -static-libsan
MLX_DIR		:= ./MLX42
LIBFT_DIR	:= ./libft

HEADERS	:= -I ./include -I $(MLX_DIR)/include -I $(LIBFT)/include
MLX42	:= $(MLX_DIR)/build/libmlx42.a
LIBFT	:= $(LIBFT_DIR)/libft.a
SRCS	:= 	cub3d.c \
			move_player.c \
			render_walls.c \
			gnl_chk.c \
			parse.c \
			parse_map.c \
			parse_map_validate.c \
			parse_utils.c \
			tokenize.c \
			errors.c \
			frees.c \
			
OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(MLX42):
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(OBJS) $(MLX42)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42) $(MLXFLAGS) $(HEADERS) -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS)
	@rm -rf $(MLX_DIR)/build

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re