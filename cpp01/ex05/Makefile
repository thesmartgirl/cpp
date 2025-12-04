CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = harl

SRCS = main.cpp Harl.cpp

OBJ = $(SRCS:.cpp=.o)
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)
clean:
	rm -f $(NAME)
fclean: clean
	rm -f $(NAME)
re: fclean name
.PHONY: clean fclean re name
