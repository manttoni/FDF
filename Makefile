# Source files
SRCS = color.c boolean.c data.c math.c grid.c draw.c fdf.c
SRC_DIR = src/

# Object files
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(SRC_DIR), $(OBJS))

# Library paths and files
LIBFT = lib/libft/libft.a
FT_PRINTF = lib/ft_printf/libftprintf.a
MLX = lib/mlx/libmlx.a
GET_NEXT_LINE = lib/get_next_line/get_next_line.a

# Include directories
INCLUDES = -Ilib/libft -Ilib/ft_printf -Ilib/get_next_line -Ilib/mlx

# All libraries
LIBS = $(LIBFT) $(FT_PRINTF) $(MLX) $(GET_NEXT_LINE)

# Path to library directories
LIB_DIRS = lib/libft lib/ft_printf lib/mlx lib/get_next_line

# Target to build
all: $(LIBS) fdf

# Link object files with libraries to create the final executable
fdf: $(OBJS) $(LIBS)
	cc -g -O2 -Wall -Wextra -Werror $(OBJS) $(LIBFT) $(FT_PRINTF) $(MLX) $(GET_NEXT_LINE) -o fdf -Lmlx -lXext -lX11 -lm -lbsd

# Rule to build object files from source files
$(SRC_DIR)%.o: $(SRC_DIR)%.c
	cc -g -Wall -Wextra -Werror $(INCLUDES) -c $< -o $@

# Rules to build libraries
$(MLX):
	$(MAKE) -C lib/mlx

$(LIBFT):
	$(MAKE) -C lib/libft

$(FT_PRINTF): $(LIBFT)
	$(MAKE) -C lib/ft_printf

$(GET_NEXT_LINE): $(LIBFT)
	$(MAKE) -C lib/get_next_line

# Clean object files and libraries
clean:
	$(MAKE) -C lib/libft clean
	$(MAKE) -C lib/ft_printf clean
	$(MAKE) -C lib/mlx clean
	$(MAKE) -C lib/get_next_line clean
	rm -f $(OBJS)

# Clean and remove the executable
fclean: clean
	$(MAKE) -C lib/libft fclean
	$(MAKE) -C lib/ft_printf fclean
	$(MAKE) -C lib/get_next_line fclean
	rm -f fdf

# Rebuild everything
re: fclean all

# Declare phony targets
.PHONY: all clean fclean re $(LIB_DIRS)

