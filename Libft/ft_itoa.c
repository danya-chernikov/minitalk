/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 04:35:25 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/13 17:27:29 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stddef.h>
#include <stdlib.h>

static char	*itoa_alloc(int size);
static void	itoa_sign_check(char *buf, int n, int *i);

char	*ft_itoa(int n)
{
	int		i;
	long	num;
	char	*buf;
	char	dnum;

	i = 0;
	dnum = 0;
	num = n;
	if (n < 0)
	{
		num = -num;
		dnum = 1;
	}
	buf = itoa_alloc(dnum + ft_count_digits(n) + 1);
	if (buf == NULL)
		return (NULL);
	while (num != 0)
	{
		buf[i] = (num % 10) + '0';
		num /= 10;
		i++;
	}
	itoa_sign_check(buf, n, &i);
	buf[i] = '\0';
	return (ft_reverse_str(buf));
}

static char	*itoa_alloc(int size)
{
	char	*buf;

	buf = (char *)malloc(size * sizeof(char));
	if (buf == NULL)
		return (NULL);
	return (buf);
}

static void	itoa_sign_check(char *buf, int n, int *i)
{
	if (n == 0)
	{
		buf[0] = '0';
		(*i) = 1;
	}
	else if (n < 0)
	{
		buf[*i] = '-';
		(*i)++;
	}
}
