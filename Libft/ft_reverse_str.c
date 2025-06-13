/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:23:24 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/13 19:23:25 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_reverse_str(char *str)
{
	size_t	i;
	size_t	slen;
	char	tmp;

	i = 0;
	slen = ft_strlen(str);
	while (i < slen >> 1)
	{
		tmp = str[i];
		str[i] = str[slen - i - 1];
		str[slen - i - 1] = tmp;
		i++;
	}
	return (str);
}
