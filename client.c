/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:23:50 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/14 16:10:49 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Usage: client [SERVER_PID]\n");
		exit(EXIT_FAILURE);
	}
	ft_printf("Hi! I am %s\n", argv[0]);

	ft_printf("argc = %d\n", argc);

	pid_t pid = ft_atoi(argv[1]);

	char *msg = argv[2];

	ft_printf("Trying to send the message \"%s\" to the process with PID %d\n", msg, pid);

	struct rlimit limit;
	if (getrlimit(RLIMIT_STACK, &limit) == 0)
	{
		ft_printf("Stack limit = %ld and %ld\n", limit.rlim_cur, limit.rlim_max);
	}
	else
	{
		ft_printf("getrlimit failed");
	}

	int ret = kill(pid, 0); // check if we have permission to send a signal
	if (!ret) // we do have permission
	{
		ret = kill(pid, SIGUSR1);
		if (ret)
		{
			ft_printf("Error: cannot send a signal\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		ft_printf("Error: cannot send a signal due to the lack of permission\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}
