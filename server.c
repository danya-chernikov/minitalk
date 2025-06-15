/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:23:57 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/15 18:27:36 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static void signal_handler(int signo)
{
	ft_printf("SIGUSR1 was caught\n");
	ft_printf("signo = %d\n", signo);
}

/*void signal_handler(int signo, siginfo_t *si, void *ucontext)
{

}*/

/* The default kernel-level limit for the maximum size allowed for the
 * combined argument (argv) and environment (envp) passed to a new process
 * via exec() on my machine is 2MB (512 pages × 4096 bytes). */
int main(int argc, char **argv)
{
	ft_printf("Hi! I am %s\n", argv[0]);

	pid_t my_pid = getpid();

	ft_printf("My PID is: %d\n", my_pid);

	ft_printf("argc = %d\n", argc);

	struct rlimit limit;
	if (getrlimit(RLIMIT_STACK, &limit) == 0)
	{
		ft_printf("Stack limit = %ld and %ld\n", limit.rlim_cur, limit.rlim_max);
	}
	else
	{
		ft_printf("getrlimit failed");
	}

	if (signal(SIGUSR1, signal_handler) == SIG_ERR)
	{
		ft_printf("Cannot handle SIGUSR1\n");
		exit(EXIT_FAILURE);
	}

	for (;;)
		pause();

	return 0;
}
