# Define compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./include

# Define source files for main library
SOURCES = ft_isalnum.c \
		  ft_isalpha.c \
		  ft_isascii.c \
		  ft_isdigit.c \
		  ft_isprint.c \
		  ft_strlen.c \
		  ft_tolower.c \
		  ft_toupper.c \
		  ft_bzero.c \
		  ft_memset.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_strchr.c \
		  ft_strrchr.c \
		  ft_strcmp.c \
		  ft_strncmp.c \
		  ft_strlcpy.c \
		  ft_strlcat.c \
		  ft_atoi.c \
		  ft_calloc.c \
		  ft_strnstr.c \
		  ft_strdup.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_substr.c \
		  ft_strjoin.c \
		  ft_strtrim.c \
		  ft_itoa.c \
		  ft_striteri.c \
		  ft_strmapi.c \
		  ft_split.c \
		  ft_lstnew.c \
		  ft_lstadd_front.c \
		  ft_lstsize.c \
		  ft_lstlast.c \
		  ft_lstadd_back.c \
		  ft_lstdelone.c \
		  ft_lstclear.c \
		  ft_lstiter.c \
		  ft_lstmap.c \
		  get_next_line.c \
		  get_next_line_utils.c


# Generate object file names from source file names
OBJECTS = $(SOURCES:.c=.o)

# Define library name
NAME = libft.a

# Rule to build the main library
$(NAME):
	$(CC) $(CFLAGS) -c $(SOURCES) $(INCLUDE)
	ar -rs $(NAME) $(OBJECTS)

# Default target, builds the main library
all: $(NAME)

# Rule to clean and rebuild the library
re: fclean all

# Rule to clean up object files
clean:
	rm -f $(OBJECTS)

# Rule to clean up object files AND library
fclean: clean
	rm -f $(NAME)

# Mark targets that don't correspond to file names
.PHONY: all re clean fclean
