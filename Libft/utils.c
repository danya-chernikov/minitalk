/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 04:35:00 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/13 17:30:51 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>
#include <stdlib.h>

/* Determines if the symbol after the i position is
 * a percent symbol. If so, it prints '%' and skips
 * the i + 1 position. Returns 1 if the next symbol
 * after '%' is percent and 0 if not */
int	next_sym_is_percent(char const *format, int *i)
{
	char	percent;

	percent = '%';
	if (format[*i + 1] == '%')
	{
		if (write(1, &percent, (size_t)1) == -1)
			return (-1);
		*i += 2;
		return (1);
	}
	return (0);
}

/* Determines if a symbol
 * belongs to a conversion
 * specifier symbols group */
int	is_conv(char ch)
{
	char const	*convs;
	int			i;

	convs = "cspdiuxX\0";
	i = 0;
	while (convs[i] != '\0')
	{
		if (ch == convs[i])
			return (1);
		i++;
	}
	return (0);
}

int	printf_putstr_fd(char *s, int fd)
{
	int	slen;

	slen = ft_strlen(s);
	if (write(fd, s, slen) == -1)
		return (-1);
	return (0);
}

char	*ft_itoa_pos(unsigned int n)
{
	int		i;
	char	*buf;

	if (n == 0)
	{
		buf = (char *)malloc(2 * sizeof(char));
		if (buf == NULL)
			return (NULL);
		buf[0] = '0';
		buf[1] = '\0';
		return (buf);
	}
	i = 0;
	buf = (char *)malloc((ft_count_digits(n) + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	while (n != 0)
	{
		buf[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	buf[i] = '\0';
	return (ft_reverse_str(buf));
}
