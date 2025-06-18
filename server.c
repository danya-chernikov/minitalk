/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:23:57 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/18 20:01:15 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "server.h"

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

static t_client_state	g_clients[MAX_CLIENTS];

/* The default kernel-level limit for the maximum size allowed for the
 * combined argument (argv) and environment (envp) passed to a new process
 * via exec() on my machine is 2MB (512 pages × 4096 bytes). */
int	main(int argc, char **argv)
{
	pid_t				my_pid;
	struct sigaction	sig;

	(void)argc;
	(void)argv;
	my_pid = getpid();
	ft_printf("My PID is: %d\n", my_pid);
	sig.sa_sigaction = signal_handler;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGUSR1);
	sigaddset(&sig.sa_mask, SIGUSR2);
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig, NULL) == -1)
	{
		ft_printf("Cannot handle SIGUSR1\n");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sig, NULL) == -1)
	{
		ft_printf("Cannot handle SIGUSR2\n");
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (0);
}

static t_client_state	*get_client_state(pid_t pid)
{
	int	i;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (g_clients[i].active && g_clients[i].pid == pid)
			return (&g_clients[i]);
		i++;
	}
	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (!g_clients[i].active)
		{
			g_clients[i].pid = pid;
			g_clients[i].cur_char = 0;
			g_clients[i].bits_recv = 0;
			g_clients[i].active = 1;
			return (&g_clients[i]);
		}
		i++;
	}
	return (NULL);
}

static void	signal_handler(int signo, siginfo_t *sinfo, void *ucontext)
{
	t_client_state	*client;

	(void)ucontext;
	client = get_client_state(sinfo->si_pid);
	if (!client)
		return ;
	if (signo == SIGUSR1)
		client->cur_char |= (1 << client->bits_recv);
	client->bits_recv++;
	if (client->bits_recv == 8)
	{
		if (client->cur_char == '\0')
		{
			ft_printf("\n");
			client->pid = 0;
			client->cur_char = 0;
			client->bits_recv = 0;
			client->active = 0;
		}
		else
			ft_printf("%c", client->cur_char);
		client->cur_char = 0;
		client->bits_recv = 0;
	}
	kill(sinfo->si_pid, SIGUSR1);
}
