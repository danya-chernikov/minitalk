/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:24:30 by dchernik          #+#    #+#             */
/*   Updated: 2025/06/13 19:24:31 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	psignal(1, "kekeke");

	char *sig_name = strsignal(15);
	printf("%s\n", sig_name);

	sig_name = strsignal(9);
	printf("%s\n", sig_name);

	return 0;
}
