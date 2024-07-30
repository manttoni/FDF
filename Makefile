# Source files
SRCS = math.c grid.c draw.c error.c fdf.c

# Object files
OBJS = $(SRCS:.c=.o)

# Library paths and files
LIBFT = libft/libft.a
FT_PRINTF = ft_printf/libftprintf.a
MLX = mlx/libmlx.a
GET_NEXT_LINE = get_next_line/get_next_line.a

# Include directories
INCLUDES = -Ilibft -Ift_printf -Iget_next_line -Imlx

# All libraries
LIBS = $(LIBFT) $(FT_PRINTF) $(MLX) $(GET_NEXT_LINE)

# Path to library directories
LIB_DIRS = libft ft_printf mlx get_next_line

# Target to build
all: $(LIBS) fdf

# Link object files with libraries to create the final executable
fdf: $(OBJS) $(LIBS)
	cc -g -Wall -Wextra -Werror $(OBJS) $(LIBFT) $(FT_PRINTF) $(MLX) $(GET_NEXT_LINE) -o fdf -Lmlx -lmlx -lXext -lX11 -lm -lbsd

# Rule to build object files from source files
%.o: %.c
	cc -g -Wall -Wextra -Werror $(INCLUDES) -c $< -o $@

# Rules to build libraries
$(MLX):
	$(MAKE) -C mlx

$(LIBFT):
	$(MAKE) -C libft

$(FT_PRINTF): $(LIBFT)
	$(MAKE) -C ft_printf

$(GET_NEXT_LINE): $(LIBFT)
	$(MAKE) -C get_next_line

# Clean object files and libraries
clean:
	$(MAKE) -C libft clean
	$(MAKE) -C ft_printf clean
	$(MAKE) -C mlx clean
	$(MAKE) -C get_next_line clean
	rm -f *.o

# Clean and remove the executable
fclean: clean
	$(MAKE) -C libft fclean
	$(MAKE) -C ft_printf fclean
	$(MAKE) -C get_next_line fclean
	rm -f fdf

# Rebuild everything
re: fclean all

# Declare phony targets
.PHONY: all clean fclean re $(LIB_DIRS)

