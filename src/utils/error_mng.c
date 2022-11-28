/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 22:57:22 by mgueifao          #+#    #+#             */
/*   Updated: 2021/12/27 15:24:58 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_string.h"

#include "minishell.h"

//Error output function is used to output an error msg based on the error type
//it received.
int	error_output(char type, int i, char *str)
{
	if (i < 0)
		i = 0;
	if (type == 'c')
	{
		printf("minishell: command not found: %s\n", g_mini.argv[i]);
		g_mini.exit_status = 127;
	}
	else if (type == 'd')
	{
		printf("minishell: cd: %s: No such file or directory\n", g_mini.argv[i]);
		g_mini.exit_status = 1;
	}
	else if (type == 's')
	{
		printf("minishell: special character not defined: %s\n", g_mini.argv[i]);
		g_mini.exit_status = 33;
	}
	else if (type == 'i')
	{
		printf("minishell: %s: No such file or directory\n", str);
		g_mini.exit_status = 1;
	}
	return (g_mini.exit_status);
}
