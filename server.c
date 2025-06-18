/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:23:57 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/18 16:20:23 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * 1. Maintain  a separate state for each client (by PID);
 * 2. Track which bit position yu are expecting for each client;
 * 3. Implement an end-of-message marker (NULL terminator);
 * 4. Make sure signal handling is reentrant;
 * 5. Block signals during critial sections. */

#include "libft.h"

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

# define MAX_CLIENTS 100

typedef struct s_client_state
{
	pid_t			pid;
	unsigned char	cur_char;
	unsigned char	bits_recv; /* bits received */
	int				active;
} t_client_state;

static t_client_state clients[MAX_CLIENTS]; /* must be global */

static t_client_state *get_client_state(pid_t pid)
{
	int	i;
	
	// Check if a client with this PID already exists
	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (clients[i].active && clients[i].pid == pid)
			return (&clients[i]);
		i++;
	}

	// If we are here, the PID doesn't exist
	// and we need to find an empty slot to
	// initialize our new client
	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (!clients[i].active)
		{
			clients[i].pid = pid;
			clients[i].cur_char = 0;
			clients[i].bits_recv = 0;
			clients[i].active = 1;
			return (&clients[i]);
		}
		i++;
	}

	return (NULL); // There is no space for a new client
}

static void signal_handler(int signo, siginfo_t *sinfo, void *ucontext)
{
	/* Do not use this variable */
	(void)ucontext;

	t_client_state *client = get_client_state(sinfo->si_pid);
	if (!client)
		return ; // Couldn't allocate client state

	if (signo == SIGUSR1) // We need to set a bit in the bits_cnt position from lower bit
		client->cur_char |= (1 << client->bits_recv);

	// In case of receiving SIGUSR2 do nothing cause we just don't need to set any bit

	client->bits_recv++;

	if (client->bits_recv == 8)
	{
		if (client->cur_char == '\0') // End of message
		{
			ft_printf("\n");
			// Full cleanup before client's deactivation
			client->pid = 0;
			client->cur_char = 0;
			client->bits_recv = 0;
			client->active = 0; // Should be last to prevent race conditions
		}
		else
		{
			ft_printf("%c", client->cur_char);
		}
		client->cur_char = 0;
		client->bits_recv = 0;
	}

	// Acknowledge back to client that the bit was received
	kill(sinfo->si_pid, SIGUSR1);
}

/* The default kernel-level limit for the maximum size allowed for the
 * combined argument (argv) and environment (envp) passed to a new process
 * via exec() on my machine is 2MB (512 pages × 4096 bytes). */
int main(int argc, char **argv)
{
	pid_t my_pid;
	(void)argc;
	(void)argv;

	my_pid = getpid();
	ft_printf("My PID is: %d\n", my_pid);

	struct sigaction sig;
	sig.sa_sigaction = signal_handler;
	sigemptyset(&sig.sa_mask);
	// Let's block both SIGUSR1 and SIGUSR2 during signal handling
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

	for (;;)
		pause();

	return 0;
}
