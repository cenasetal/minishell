/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 22:30:26 by mgueifao          #+#    #+#             */
/*   Updated: 2022/02/09 01:24:58 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "minishell.h"
#include "utilities.h"

#include "ft_string.h"
#include "ft_stdlib.h"

/*
*   The Path Creation function is used to differentiate between built-in program
*    calls such as ls, wc, etc, and executable programs calls with "./" or
*    "a.out".
*/
static char	*path_creation(char *path, char *cmd)
{
	char		*temp;
	char		*new_path;
	t_dl_list	*head;

	head = g_mini.env;
	if (!ft_strncmp(cmd, "./", 2) || ft_strcmp(cmd, "a.out"))
		new_path = ft_strjoin(return_env_content(g_mini.env, "PWD"), ++cmd);
	else if (!ft_strncmp(cmd, "/", 1))
		new_path = ft_strdup(cmd);
	else
	{
		temp = ft_strjoin(path, "/");
		new_path = ft_strjoin(temp, cmd);
		ft_free(temp);
		temp = NULL;
	}
	g_mini.env = head;
	return (new_path);
}

static void	create_env_array_loop(char **env)
{
	char	*temp;
	int		i;

	i = -1;
	while (g_mini.env)
	{
		temp = ft_strjoin(g_mini.env->name, "=");
		env[++i] = ft_strjoin(temp, g_mini.env->content);
		ft_free(temp);
		g_mini.env = g_mini.env->next;
		if (!g_mini.env)
			break ;
	}
	env[++i] = NULL;
}

/*
*   Copies our internal dual linked env list to a malloced array of strings.
*    Each entry of the array is also malloced using ft_strjoin function.
*/
static char	**temp_env(char **env)
{
	t_dl_list	*head;
	int			size;

	head = g_mini.env;
	size = 0;
	while (g_mini.env)
	{
		g_mini.env = g_mini.env->next;
		size++;
		if (!g_mini.env)
			break ;
	}
	g_mini.env = head;
	env = (char **)ft_malloc(sizeof(char *) * (size + 1));
	create_env_array_loop(env);
	g_mini.env = head;
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
	path = return_env_content(g_mini.env, "PATH");
	paths = ft_split((const char *)path, ':');
	g_mini.str = NULL;
	j = path_creation_loop(argv, paths, argv[i]);
	if (j == 127)
		error_output('c', 0, NULL);
	exit(127);
	return (j);
}
