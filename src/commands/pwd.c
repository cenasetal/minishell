/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:55:46 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 11:55:48 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include "minishell.h"

//Print the content of the environmental variable "PWD" from the internal
//env list (dual linked list).

int	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
		return (-1);
	printf("%s\n", pwd);
	exit(0);
	return (1);
}

//Exit function is used to flag the exit call to make sure that the main func
//free up our struct and exit the program successfully.
//free_struct function is being called inside the main loop now when the exit
//is called.
void	ft_exit(void)
{
	g_global.exit = 1;
	printf("exit\n");
}
