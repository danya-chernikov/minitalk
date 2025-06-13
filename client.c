/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:23:50 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/13 19:23:51 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Usage: client [SERVER_PID]\n");
		exit(1);
	}
	ft_printf("Hi! I am %s\n", argv[0]);

	ft_printf("argc = %d\n", argc);

	return 0;
}
