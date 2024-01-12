# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 15:07:52 by asfletch          #+#    #+#              #
#    Updated: 2024/01/12 15:11:23 by asfletch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = main.c \

BONUS = \

CC =			gcc
RM =			rm -f
CFLAGS =		-Wall -Wextra -Werror -g
OBJS =			$(SRCS:.c=.o)
BONUS_OBJS =	$(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
		rm -f $(NAME)

re:		fclean all

bonus: $(OBJS) $(BONUS_OBJS)
		ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY: all clean fclean re