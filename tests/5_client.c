/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_client.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:24:35 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/17 15:16:59 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage: client [SERVER_PID]\n");
		exit(EXIT_FAILURE);
	}
	printf("Hi! I am %s\n", argv[0]);

	printf("argc = %d\n", argc);

	pid_t pid = atoi(argv[1]);

	char *msg = argv[2];

	printf("Trying to send the message \"%s\" to the process with PID %d\n", msg, pid);

	int ret = kill(pid, 0); // check if we have permission to send a signal
	if (!ret) // we do have permission
	{
		ret = kill(pid, SIGUSR1);
		{
			printf("Error: cannot send a signal\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		printf("Error: cannot send a signal due to the lack of permission\n");
		exit(EXIT_FAILURE);
	}

	return (0);
}
