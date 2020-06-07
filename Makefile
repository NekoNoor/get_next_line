# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nschat <nschat@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/31 21:17:26 by nschat        #+#    #+#                  #
#    Updated: 2020/05/31 22:14:56 by nschat        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror

SRC = get_next_line.c \
	  get_next_line_utils.c

SRC_TEST = main.c

ODIR = obj
OBJ = $(addprefix $(ODIR)/,$(SRC:.c=.o))

NAME = libgnl.a

vpath %.c src

.PHONY: clean fclean

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) rcs $@ $^

$(ODIR)/%.o: %.c
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME) | $(SRC_TEST)
	$(CC) $(CFLAGS) -I. -L. $| -o $@ -lgnl

clean:
	$(RM) -r $(ODIR)

fclean: clean
	$(RM) $(NAME) test

re: fclean all
