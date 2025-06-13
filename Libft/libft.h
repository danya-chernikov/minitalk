/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:40:28 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/13 19:32:55 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdarg.h>

/* get_next_line defines */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define EXIT			0
# define READ			1
# define ALLOC			2
# define END			3
# define AGAIN			4

/* FD		  - a file descriptor;
 * RLEN		  - bytes read from `fd` (FD);
 * I		  - an auxiliary coutner variable;
 * RES		  - result of a function execution;
 * PRIV_MEM_S - previously allocated memory size. */
# define FD				0
# define BUF_POS		1
# define LINE_POS		2
# define RLEN			3
# define LINE_LEN		4
# define I				5
# define RES			6
# define PRIV_MEM_S		7

/* NORM  - normal execution. Means to do nothing;
 * RET   - indicate that the `line` must be returned;
 * BREAK - break from the main loop must be performed;
 * CONT  - continue must be applied on the main loop. */
# define NORM			0
# define RET			1
# define BREAK			2
# define CONT			3

/* Lists defines */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* Newly added functions */
char		*ft_int_to_hex(unsigned long long num, int dcase);
char		*ft_reverse_str(char *str);
int			ft_count_digits(long long n);

/* get_next_line functions */
/* get_next_line.c */
char		*get_next_line(int fd);
int			loop_alg(char *buf, char **line, long long *v, int *flags);
int			get_chunk(char *buf, char **line, long long *v, int *flags);
void		process_new_line(char *buf, char **line, long long *v, int *flags);
int			process_end_chunk(char **line, long long *v, int *flags);

/* get_next_line_utils.c */
int			init(char *buf, char **line, long long *v, int *flags);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int			alloc_mem(char **line, long long *v, int *flags);
void		check_reaching_end(long long *v, int *flags);
void		clear_func_state(char **line, long long *v, int *flags);

/* Original Libft functions */
/* First part */
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *s);

/* Second part */
int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_substr(char const *s, unsigned int start, size_t len);

/* Lists */
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* printf functions */
/* ft_printf.c */
int			ft_printf(char const *format, ...);
int			parse_format_str(char const *format, va_list *vl, int *pbytes);
int			process_percent(char const *fstr, va_list *vl, int *pbytes, int *i);
int			process_not_percent(char const *f, va_list *vl, void **pack);
int			process_conv(char const *format, va_list *vl, int cpos);

/* non_numeric.c */
int			char_conv(va_list *vl);
int			string_conv(va_list *vl);
int			ptr_conv(va_list *vl);

/* numeric.c */
int			nbr_conv(va_list *vl);
int			u_nbr_conv(va_list *vl);
int			hex_conv(va_list *vl, int dcase);
int			hex_not_zero(unsigned int hex_arg, int dcase, int *len);

/* utils.c */
int			next_sym_is_percent(char const *format, int *i);
int			is_conv(char ch);
int			printf_putstr_fd(char *s, int fd);
char		*ft_itoa_pos(unsigned int n);

/* packer.c */
void		**pack_args(int nargs, ...);

#endif
