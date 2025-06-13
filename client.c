#include "libft.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Usage: client [SERVER_PID]\n");
		exit(1);
	}
	ft_printf("Hi! I am %s\n", argv[0]);

	ft_printf("argc = %d\n", argc);

	return 0;
}
