/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:23:50 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/18 19:57:42 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "client.h"

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

volatile sig_atomic_t	g_ack_recv = 0;

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_printf("Usage: ./client [SERVER_PID]\n");
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (send_message(&pid, argv[2]))
		exit(EXIT_FAILURE);
	return (0);
}

void	ack_handler(int sig)
{
	(void)sig;
	g_ack_recv = 1;
}

/* Returns 0 on success */
int	send_message(pid_t *pid, const char *msg)
{
	int	ret;

	ft_printf("Sending the message...\n");
	if (signal(SIGUSR1, ack_handler) == SIG_ERR)
	{
		ft_printf("Cannot handle SIGUSR2\n");
		return (1);
	}
	ret = kill(*pid, 0);
	if (!ret)
	{
		if (send_string(pid, msg))
		{
			ft_printf("Error: cannot send a signal\n");
			return (1);
		}
	}
	else
	{
		ft_printf("Error: cannot send signal due to lack of permission\n");
		return (1);
	}
	ft_printf("Message sent successfully\n");
	return (0);
}

int	send_string(pid_t *pid, const char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (send_char(pid, str[i]))
			return (1);
		i++;
	}
	if (send_char(pid, '\0'))
		return (1);
	return (0);
}

/* On success returns 0;
 * We use unsigned char cause we want
 * to be able to represent all ASCII table */
int	send_char(pid_t *pid, unsigned char symbol)
{
	int	i;
	int	ret;
	int	signal;

	i = 0;
	while (i < 8)
	{
		if ((int)symbol & (1 << i))
			signal = SIGUSR1;
		else
			signal = SIGUSR2;
		ret = kill(*pid, signal);
		if (ret)
			return (1);
		g_ack_recv = 0;
		while (!g_ack_recv)
			pause();
		if (usleep(DELAY))
			return (1);
		i++;
	}
	return (0);
}
