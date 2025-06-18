/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:23:50 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/18 16:43:23 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

volatile sig_atomic_t ack_recv = 0;

void	ack_handler(int sig)
{
	(void)sig;
	ack_recv = 1;
}

/* On success returns 0;
 * We use unsigned char cause we want
 * to be able to represent all ASCII table */
int	send_char(pid_t *pid, unsigned char symbol)
{
	int	i;
	int	ret;

	i = 0;
	while (i < 8)
	{
		if ((int)symbol & (1 << i)) // bit is 1
		{
			ret = kill(*pid, SIGUSR1);
			if (ret)
				return (1);
			ack_recv = 0;
			// waiting for receiving confirmation from the server
			while (!ack_recv)
				pause();
		}
		else // bit is 0
		{
			ret = kill(*pid, SIGUSR2);
			if (ret)
				return (1);
			ack_recv = 0;
			while (!ack_recv)
				pause();
		}
		// It seems to me the delay should be at least 1000000/(100*8) = 125 microseconds
		if (usleep(125)) // sleep for 50 milliseconds (1/20 of a second)
			return (1); // ERROR
		i++;
	}
	return (0);
}

int	send_string(pid_t *pid, char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (send_char(pid, str[i]))
			return (1); // ERROR
		i++;
	}
	if (send_char(pid, '\0')) // Zero byte goes at the end
		return (1); // ERROR

	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*msg;
	int		ret;

	if (argc != 3)
	{
		ft_printf("Usage: ./client [SERVER_PID]\n");
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	msg = argv[2];
	ft_printf("Trying to send the message \"%s\" to the process with PID %d\n", msg, pid);
	if (signal(SIGUSR1, ack_handler) == SIG_ERR)
	{
		ft_printf("Cannot handle SIGUSR2\n");
		exit(EXIT_FAILURE);
	}
	ret = kill(pid, 0); // Check if we have permission to send a signal
	if (!ret) // We do have permission
	{
		if (send_string(&pid, msg))
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
	return (0);
}
