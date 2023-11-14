SRCS = ./srcs/parse/ft_parse.c \
		./srcs/parse/utilslibft.c \
		./srcs/parse/map_attr_add_data.c \
		./srcs/parse/utils.c \
		./srcs/main.c
NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
OBJS = $(SRCS:%.c=%.o)
LIBFT = ./srcs/libarys/libft/libft.a
MLX = ./srcs/libarys/mlx/libmlx.a
GNL = ./srcs/libarys/get_next_line/get_next_line.c \
		./srcs/libarys/get_next_line/get_next_line_utils.c

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "\n"
	@$(CC) $(CFLAGS) $(OBJS) $(GNL) $(LIBFT) $(MLX) -o $(NAME)
	@echo "\033[5m\033[32mBuild successfull !\033[25m\033[0m"

%.o: %.c
	@printf "\033[33mGenerating Cub3D objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

$(LIBFT):
	@make -C ./srcs/libarys/libft
	@make bonus -C ./srcs/libarys/libft

$(MLX):
	@make -C ./srcs/libarys/mlx

clean:
	$(RM) $(OBJS)
	@make clean -C ./srcs/libarys/libft
	@make clean -C ./srcs/libarys/mlx	

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(MLX)
		
re:	fclean all


.PHONY: all re clean fclean