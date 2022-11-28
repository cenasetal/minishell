/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:55:46 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 16:10:13 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include "minishell.h"

int	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
		return (-1);
	printf("%s\n", pwd);
	exit(0);
	return (1);
}

void	ft_exit(void)
{
	g_global.exit = 1;
	printf("exit\n");
}
