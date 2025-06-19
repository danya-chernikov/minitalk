/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:07:47 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/19 02:53:08 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(CLIENT_H)
# define CLIENT_H

# include <signal.h>

/* 1 microsecond */
# define DELAY			700
# define LOG_FILE_NAME	"client.log"

void	ack_handler(int sig);
int		send_message(pid_t *pid, const char *msg);
int		send_string(pid_t *pid, const char *str);
int		send_char(pid_t *pid, unsigned char symbol);

#endif
