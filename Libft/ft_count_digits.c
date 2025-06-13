/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:22:00 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/13 19:22:01 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_digits(long long n)
{
	int	num;

	num = 0;
	if (n < 0)
		n = -n;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		num++;
	}
	return (num);
}
