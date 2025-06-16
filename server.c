/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:23:57 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/16 19:42:54 by dchernik         ###   ########.fr       */
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
/* REENTRANCY!!! I need to prohibit
 * the processing of any signals while
 * the signal handler function is working */
static void signal_handler(int signo, siginfo_t *sinfo, void *ucontext)
{
	ucontext = NULL;

	// the same as position of the bit to set in the g_recv_char
	static unsigned char bits_cnt = 0;

	if (signo == SIGUSR1) // we need to set a bit in the bits_cnt position from lower bit
		g_recv_char |= (1 << bits_cnt);
	// in case of receiving SIGUSR2 do nothing cause we just don't need to set any bit

	++bits_cnt;

	if (bits_cnt == 8)
	{
		//write(1, (char *)&g_recv_char, 1);
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

	struct sigaction sig;
	sig.sa_sigaction = signal_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;

	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Cannot handle SIGUSR1\n");
		exit(EXIT_FAILURE);
	}

	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Cannot handle SIGUSR2\n");
		exit(EXIT_FAILURE);
	}

	for (;;)
		pause();

	return 0;
}
