# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gekido <gekido@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 15:01:48 by rbourkai          #+#    #+#              #
#    Updated: 2025/03/25 00:56:18 by gekido           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror
SRC_DIR = srcs
INC_DIR = includes

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/parsing.c \
       $(SRC_DIR)/init.c \
       $(SRC_DIR)/routine.c \
       $(SRC_DIR)/monitoring.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/cleanup.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re