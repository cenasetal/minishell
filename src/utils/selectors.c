/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selectors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:51 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 12:00:53 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "commands.h"

static int	screening_two(int i)
{
	if (ft_strcmp(g_global.argv[i], "pwd"))
		ft_pwd();
	else if (ft_strcmp(g_global.argv[i], "export"))
		ft_export(g_global.argv);
	else if (ft_strcmp(g_global.argv[i], "node"))
	{
		if (ft_strlen(g_global.argv[i]) > 0)
			ft_lstnode_print(g_global.env, g_global.argv[i + 1]);
	}
	else if (ft_strcmp(g_global.argv[i], "unset"))
		ft_unset(g_global.env, g_global.argv, i);
	else
		i = 1;
	return (i);
}

int	screening_one(char **argv)
{
	int	i;

	i = 0;
	if (g_global.argv)
	{
		if (ft_strcmp(argv[i], "exit"))
			ft_exit();
		else if (ft_strcmp(argv[i], "echo"))
			ft_echo(argv);
		else if (ft_strcmp(argv[i], "cd"))
			i = ft_cd(argv);
		else if (ft_strcmp(argv[i], " "))
			printf("\n");
		else if (ft_strcmp(argv[i], "env"))
			ft_env(g_global.env);
		else
			i = screening_two(i);
	}
	return (i);
}

void	cmd_selector(char **argv)
{
	if (argv[0])
	{
		if (ft_strcmp(argv[0], "echo"))
			ft_echo(argv);
		else if (ft_strcmp(argv[0], "env"))
			ft_env(g_global.env);
		else if (ft_strcmp(argv[0], "export"))
			ft_export(argv);
		else if (ft_strcmp(argv[0], "pwd") || ft_strcmp(argv[0], "PWD"))
			ft_pwd();
		else if (ft_strcmp(argv[0], "unset"))
			ft_unset(g_global.env, argv, 0);
		else if (ft_strcmp(argv[0], "cd"))
			ft_cd(argv);
		else
			ft_execve(argv, 0);
	}
}

int	cmd_identifier(char **argv)
{
	int	i;

	i = 0;
	if (argv)
	{
		if (ft_strcmp(argv[i], "exit"))
			i = 0;
		else if (ft_strcmp(argv[i], "cd"))
			i = 0;
		else if (ft_strcmp(argv[i], " "))
			i = 0;
		else if (ft_strcmp(argv[i], "export") && argv[i + 1] != NULL)
			i = 0;
		else if (ft_strcmp(argv[i], "node"))
			i = 0;
		else if (ft_strcmp(argv[i], "unset") && argv[i + 1] != NULL)
			i = 0;
		else
			i = 1;
	}
	return (i);
}
