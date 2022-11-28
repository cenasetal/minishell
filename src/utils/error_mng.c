/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:22 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 11:59:23 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include "minishell.h"

//Error output function is used to output an error msg based on the error type
//it received.
int	error_output(char type, int i, char *str)
{
	if (i < 0)
		i = 0;
	if (type == 'c')
	{
		printf("minishell: command not found: %s\n", g_global.argv[i]);
		g_global.exit_status = 127;
	}
	else if (type == 'd')
	{
		printf("minishell: cd: %s: No such file or directory\n", g_global.argv[i]);
		g_global.exit_status = 1;
	}
	else if (type == 's')
	{
		printf("minishell: special character not defined: %s\n", g_global.argv[i]);
		g_global.exit_status = 33;
	}
	else if (type == 'i')
	{
		printf("minishell: %s: No such file or directory\n", str);
		g_global.exit_status = 1;
	}
	return (g_global.exit_status);
}
