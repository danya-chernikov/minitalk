#include "libft.h"

#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	ft_printf("Hi! I am %s\n", argv[0]);

	pid_t my_pid = getpid();

	ft_printf("My PID is: %d\n", my_pid);

	ft_printf("argc = %d\n", argc);

	return 0;
}
