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

int		si_signo
int		si_errno
int		si_code
pit_t	si_pid
uid_t	si_uid
int		si_status
clock_t	si_utime
clock_t	si_stime
sigval_t	si_value
int		si_int
void		*si_ptr
void		*si_addr
int		si_band
int		si_fd

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
