/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:23:57 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/16 18:30:57 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

unsigned char g_recv_char = 0;

/* The zero byte cannot be received */
static void signal_handler(int signo)
{
	static unsigned char bits_cnt = 0; // the same as position of the bit to set in the g_recv_char

	/*ft_printf("SIGUSR1 was caught\n");
	ft_printf("signo = %d\n", signo);*/


	if (signo == SIGUSR1) // we need to set a bit in the bits_cnt position from lower bit
	{
		g_recv_char |= (1 << bits_cnt);
	}
	else if (signo == SIGUSR2)
	{
		// do nothing cause we just don't need to set any bit
	}
	else
	{
		ft_printf("Error: Some other signal was received\n");
	}

	++bits_cnt;

	if (bits_cnt == 8)
	{
		ft_printf("%c", g_recv_char);
		g_recv_char = 0;
		bits_cnt = 0;
	}
}

/* The default kernel-level limit for the maximum size allowed for the
 * combined argument (argv) and environment (envp) passed to a new process
 * via exec() on my machine is 2MB (512 pages × 4096 bytes). */
int main(int argc, char **argv)
{
	ft_printf("Hi! I am %s\n", argv[0]);

	pid_t my_pid = getpid();

	ft_printf("My PID is: %d\n", my_pid);

	ft_printf("argc = %d\n", argc);

	if (signal(SIGUSR1, signal_handler) == SIG_ERR)
	{
		ft_printf("Cannot handle SIGUSR1\n");
		exit(EXIT_FAILURE);
	}

	if (signal(SIGUSR2, signal_handler) == SIG_ERR)
	{
		ft_printf("Cannot handle SIGUSR2\n");
		exit(EXIT_FAILURE);
	}

	for (;;)
		pause();

	return 0;
}
