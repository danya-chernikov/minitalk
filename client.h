#if !defined(CLIENT_H)
# define CLIENT_H

# include <signal.h>

/* 1 microsecond */
# define DELAY	1000

void	ack_handler(int sig);
int		send_message(pid_t *pid, const char *msg);
int		send_string(pid_t *pid, const char *str);
int		send_char(pid_t *pid, unsigned char symbol);

#endif
