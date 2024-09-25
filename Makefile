NAME=pipex
CC=cc
CFLAGS= -Wall -Wextra -Werror
SRCS := srcs/child_process.c \
	srcs/command_exec.c \
	srcs/ft_putstr_fd.c \
	srcs/ft_split.c \
	srcs/ft_strjoin.c \
	srcs/ft_strlen.c \
	srcs/ft_strnstr.c \
	srcs/parent_process.c \
	srcs/pathfinder.c \
	srcs/main.c \

OBJ= $(SRCS:.c=.o)

all:    $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
