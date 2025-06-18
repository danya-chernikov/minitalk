#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

unsigned char g_recv_char = 0;

/* The zero byte cannot be received */
/* REENTRANCY!!! I need to prohibit
 * the processing of any signals while
 * the signal handler function is working */
static void signal_handler(int signo, siginfo_t *sinfo, void *ucontext)
{
	ucontext = NULL;
	printf("si_signo = %d\n", sinfo->si_signo);
	printf("si_errno = %d\n", sinfo->si_errno);
	printf("si_code = %d\n", sinfo->si_code);
	printf("si_pid = %d\n", sinfo->si_pid);
	printf("si_uid = %u\n", sinfo->si_uid);
	printf("si_status = %d\n", sinfo->si_status);
	printf("si_utime = %ld\n", sinfo->si_utime);
	printf("si_stime = %ld\n", sinfo->si_stime);
	printf("si_addr = %p\n", sinfo->si_addr);
	printf("si_band = %ld\n", sinfo->si_band);
	printf("si_fd = %d\n", sinfo->si_fd);
}

/* The default kernel-level limit for the maximum size allowed for the
 * combined argument (argv) and environment (envp) passed to a new process
 * via exec() on my machine is 2MB (512 pages × 4096 bytes). */
int main(int argc, char **argv)
{
	printf("Hi! I am %s\n", argv[0]);

	pid_t my_pid = getpid();

	printf("My PID is: %d\n", my_pid);

	printf("argc = %d\n", argc);

	struct sigaction sig;
	sig.sa_sigaction = signal_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;

	if (sigaction(SIGUSR1, &sig, NULL) == -1)
	{
		printf("Cannot handle SIGUSR1\n");
		exit(EXIT_FAILURE);
	}

	for (;;)
		pause();

	return 0;
}
