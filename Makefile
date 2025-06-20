CC=cc
LIBFT_NAME=ft
LIBFT_PATH=Libft/
CLIENT_NAME=client
SERVER_NAME=server

CFLAGS=-Wall -Werror -Wextra -pedantic-errors -O2

CLIENT_OBJS=client.o
SERVER_OBJS=server.o

all : libft $(CLIENT_NAME) $(SERVER_NAME)

libft :
	cd $(LIBFT_PATH) && $(MAKE) all # Let's build the Libft

$(CLIENT_NAME) : $(CLIENT_OBJS)
	$(CC) -L$(LIBFT_PATH) $(CLIENT_OBJS) -l$(LIBFT_NAME) -o $(CLIENT_NAME) -no-pie

$(SERVER_NAME) : $(SERVER_OBJS)
	$(CC) -L$(LIBFT_PATH) $(SERVER_OBJS) -l$(LIBFT_NAME) -o $(SERVER_NAME) -no-pie

clean :
	rm -rf $(CLIENT_OBJS) $(SERVER_OBJS)

fclean : clean
	rm -rf $(CLIENT_NAME) $(SERVER_NAME)

re : fclean all

client.o : client.c client.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c client.c

server.o : server.c server.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c server.c

.PHONY: all clean fclean re libft
