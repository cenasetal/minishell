/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 22:30:05 by mgueifao          #+#    #+#             */
/*   Updated: 2021/12/27 15:42:17 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "minishell.h"

#include "ft_string.h"

static void	echo_flag(char **argv, int i, int j, int k)
{
	if (i > k)
	{
		j = k;
		while (i > j)
		{
			if (ft_strcmp(argv[j], "$?"))
				printf("%d", g_mini.exit_status);
			else
				printf("%s", argv[j]);
			if (i > 1 + j++)
				printf(" ");
		}
		if (k == 1)
			printf("\n");
	}
}

//The Echo command function is used to print the inputed arguments provided.
//It will check for the '-n' flag which removes the new line.
//It will also print environmental varible if they are called.
void	ft_echo(char **argv)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 1;
	while (argv[i])
		i++;
	if (i >= 2 && ft_strcmp(argv[1], "-n"))
		k = 2;
	echo_flag(argv, i, j, k);
}
