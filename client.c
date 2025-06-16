/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:23:50 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/16 18:15:27 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

/*
 * typedef struct siginfo_t {
 *     int		si_signo; // signal number
 *     int		si_errno; // errno value (I SUPPOSE I SHOULD USE IT TO ENCODE AT LEAST FOUR CHARACTERS)
 *     int		si_code; signal code
 *     pit_t	si_pid; sending process's PID
 *     uid_t	si_uid; sending process's real UID
 *     int		si_status; exit value or signal ?
 *     clock_t	si_utime; user time consumed | ONLY FOR CHILD PROCESSES
 *     clock_t	si_stime; system time consumed | ONLY FOR CHILD PROCESSES
 *     sigval_t	si_value; signal payload value | ONLY WITH sigqueue() | ONLY IF A SIGNAL WAS SENT USEING sigqueue()
 *     int		si_int; POSIX.1b signal | ONLY WITH sigqueue() | ONLY FOR CHILD | JUST A UNION FIELD OF si_value
 *     void		*si_ptr; POSIX.1b signal | ONLY WITH sigqueue() | CHILD | A UNION FIELD OF si_value
 *     void		*si_addr; ONLY FOR SIGBUS,SIGFPE,SIGILL,SIGSEGV,SIGTRAP memory location that caused fault | ADDRESS OF THE OFFENDING FAULT
 *     int		si_band; ONLY FOR SIGPOLL | band event ?
 *     int		si_fd; ONLY FOR SIGPOLL | file descriptor of the file whose operation completed
 * };
 * */

/* Let's put SIGUSR1 = 1 and SIGUSR2 = 0; */

/* On success returns 0;
 * We use unsigned char cause we want
 * to be able to represent all ASCII table */
int	send_char(pid_t *pid, unsigned char symbol)
{
	int	i;
	int	ret;

	i = 0;
	while (i < 8)
	{
		if ((int)symbol & (1 << i)) // bit is 1
		{
			ret = kill(*pid, SIGUSR1);
			if (ret)
				return (1);
		}
		else // bit is 0
		{
			ret = kill(*pid, SIGUSR2);
			if (ret)
				return (1);
		}
		// It seems to me the delay should be at least 1000000/(100*8) = 125 microseconds
		if (usleep(50000)) // sleep for 50 milliseconds (1/20 of a second)
			return (1); // ERROR
		i++;
	}
	return (0);
}

int	send_string(pid_t *pid, char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (send_char(pid, str[i]))
			return (1); // ERROR
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Usage: client [SERVER_PID]\n");
		exit(EXIT_FAILURE);
	}
	ft_printf("Hi! I am %s\n", argv[0]);

	ft_printf("argc = %d\n", argc);

	pid_t pid = ft_atoi(argv[1]);

	char *msg = argv[2];

	ft_printf("Trying to send the message \"%s\" to the process with PID %d\n", msg, pid);

	int ret = kill(pid, 0); // check if we have permission to send a signal
	if (!ret) // we do have permission
	{
		if (send_string(&pid, msg))
		{
			ft_printf("Error: cannot send a signal\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		ft_printf("Error: cannot send a signal due to the lack of permission\n");
		exit(EXIT_FAILURE);
	}

	return (0);
}
