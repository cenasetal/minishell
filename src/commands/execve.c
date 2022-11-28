/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:54:28 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 16:08:49 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"

#include "libft.h"

/*
*   Finds executable in PATH if exists ele executes command with relative path
*/
static char	*path_creation(char *path, char *cmd)
{
	char		*temp;
	char		*new_path;
	t_dl_list	*head;

	head = g_global.env;
	if (!ft_strncmp(cmd, "./", 2) || ft_strcmp(cmd, "a.out"))
		new_path = ft_strjoin(return_env_content(g_global.env, "PWD"), ++cmd);
	else if (!ft_strncmp(cmd, "/", 1))
		new_path = ft_strdup(cmd);
	else
	{
		temp = ft_strjoin(path, "/");
		new_path = ft_strjoin(temp, cmd);
		ft_free(temp);
		temp = NULL;
	}
	g_global.env = head;
	return (new_path);
}

static void	create_env_array_loop(char **env)
{
	char	*temp;
	int		i;

	i = -1;
	while (g_global.env)
	{
		temp = ft_strjoin(g_global.env->name, "=");
		env[++i] = ft_strjoin(temp, g_global.env->content);
		ft_free(temp);
		g_global.env = g_global.env->next;
		if (!g_global.env)
			break ;
	}
	env[++i] = NULL;
}

static char	**temp_env(char **env)
{
	t_dl_list	*head;
	int			size;

	head = g_global.env;
	size = 0;
	while (g_global.env)
	{
		g_global.env = g_global.env->next;
		size++;
		if (!g_global.env)
			break ;
	}
	g_global.env = head;
	env = (char **)malloc(sizeof(char *) * (size + 1));
	create_env_array_loop(env);
	g_global.env = head;
	return (env);
}

/*
*   The path creation loop function is mainly used to cut down lines on the
*    execve function body. It will loop through all the possible path's found in
*    the env "PATH" ($PATH) and try to run each of them with the inputed cmd.
*/
static int	path_creation_loop(char **cmds, char **path, char *cmd)
{
	char	**env;
	char	*total;
	int		i;
	int		j;

	i = -1;
	j = -1;
	env = temp_env(NULL);
	while (path[++i])
	{
		total = path_creation(path[i], cmd);
		if ((execve(total, cmds, env) != -1))
			--j;
		ft_free(total);
		total = NULL;
		++j;
	}
	free_table(env);
	if (j == i)
		return (1);
	return (127);
}

/*
*   The execve function is used to execute various commands such as ls, wc, grep
*    etc. This commands are not mandatory but will improve the user experience
*    and they will help during the program evaluation.
*/
int	ft_execve(char **argv, int i)
{
	char	*path;
	char	**paths;
	int		j;

	if (!argv[i])
		return (0);
	path = return_env_content(g_global.env, "PATH");
	paths = ft_split((const char *)path, ':');
	g_global.str = NULL;
	j = path_creation_loop(argv, paths, argv[i]);
	if (j == 127)
		error_output('c', 0, NULL);
	exit(127);
	return (j);
}
