/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:24:26 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/13 19:24:27 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

/* handler for SIGINT and SIGTERM */
static void signal_handler(int signo)
{
	if (signo == SIGINT)
		printf ("Caught SIGINT!\n");
	else if (signo == SIGTERM)
		printf ("Caught SIGTERM!\n");
	else
	{
		/* this should never happen */
		fprintf (stderr, "Unexpected signal!\n");
		exit (EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int main(void)
{
	pid_t pid = getpid();
	printf("My PID is %d\n", pid);
	
	/* Register signal_handler as our signal handler for SIGINT */
	if (signal (SIGINT, signal_handler) == SIG_ERR)
	{
		fprintf(stderr, "Cannot handle SIGINT!\n");
		exit (EXIT_FAILURE);
	}

	/* Register signal_handler as our signa handler for SIGTERM */
	if (signal (SIGTERM, signal_handler) == SIG_ERR)
	{
		fprintf(stderr, "Cannot handle SIGTERM!\n");
		exit (EXIT_FAILURE);
	}

	/* Reset SIGPROF's behaviour to the default */
	if (signal (SIGPROF, SIG_DFL) == SIG_ERR)
	{
		fprintf(stderr, "Cannot reset SIGPROF!\n");
		exit (EXIT_FAILURE);
	}

	/* Ignore SIGHUP */
	if (signal (SIGHUP, SIG_IGN) == SIG_ERR)
	{
		fprintf(stderr, "Cannot ignore SIGHUP!\n");
		exit (EXIT_FAILURE);
	}

	for (;;)
		pause();

	return 0;
}
