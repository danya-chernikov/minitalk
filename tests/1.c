/* SIGUSR1 and SIGUSR2
 * These signals are available for user-defined purposes;
 * the kernel never raises them. Processes may use SIGUSR1
 * and SIGUSR2 for whatever purpose they like. A common use
 * is to instruct a daemon process to behave differently.
 * The default action is to terminate the process.
 * [Robert Love. Linux System Programming. p.399 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sigint_handler (int signo)
{
	printf("Caught SIGINT!\n");
	exit (EXIT_SUCCESS);
}

int main(void)
{
	if (signal (SIGINT, sigint_handler) == SIG_ERR)
	{
		fprintf(stderr, "Cannot handle SIGINT\n");
		exit (EXIT_FAILURE);
	}

	for (;;)
		pause();

	return 0;
}
