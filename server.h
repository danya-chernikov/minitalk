/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:07:52 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/19 15:20:31 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(SERVER_H)
# define SERVER_H

# include <signal.h>

typedef struct s_client_state
{
	pid_t			pid;
	unsigned char	cur_char;
	unsigned char	bits_recv;
	int				active;
}	t_client_state;

# define MAX_CLIENTS	100

static t_client_state	*get_client_state(pid_t pid);
static void				signal_handler(int signo, siginfo_t *sinfo, void *uctx);

#endif
