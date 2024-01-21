# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 15:07:52 by asfletch          #+#    #+#              #
#    Updated: 2024/01/21 15:36:28 by asfletch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:
COLOUR_GREEN = \033[0;32m
COLOUR_RED = \033[0;31m
COLOUR_BLUE = \033[0;34m
COLOUR_END = \033[0m

NAME		= pipex

LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

SRCS		= src/main.c src/parse_args.c src/utils.c src/error_free.c \
			src/the_fam.c \

INCLUDES	= -I includes -I header -I $(LIBFT_DIR)
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g $(INCLUDES)
OBJS		= $(SRCS:.c=.o)
RM			= rm -f

all: $(NAME)

$(LIBFT_LIB):
			make -C $(LIBFT_DIR)
			make -C $(LIBFT_DIR) bonus

$(NAME): $(LIBFT_LIB) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft
		echo "$(COLOUR_GREEN)Pipex compiled successfully!$(COLOUR_END)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)
		make -C $(LIBFT_DIR) clean

fclean: clean
		$(RM) $(NAME)
		make -C $(LIBFT_DIR) fclean
		echo "$(COLOUR_BLUE)Pipex cleaned successfully!$(COLOUR_END)"

re:		fclean all

.PHONY: all clean fclean re
