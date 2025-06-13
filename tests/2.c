/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:24:21 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/13 19:24:23 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sighup_handler(int signo)
{
	int fd = creat("SIGHUP_was_caught", 0644);
	if (fd == -1)
	{
		fprintf(stderr, "Could not create a file");
		exit (EXIT_FAILURE);
	}
	close(fd);
}

int main(void)
{
	if (signal (SIGHUP, sighup_handler) == SIG_ERR)
	{
		fprintf(stderr, "Cannot handle SIGHUP\n");
		exit (EXIT_FAILURE);
	}

	for (;;)
		pause();
	return 0;
}
