/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 22:29:42 by mgueifao          #+#    #+#             */
/*   Updated: 2021/12/27 17:05:45 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>

#include "minishell.h"
#include "utilities.h"

#include "ft_string.h"
#include "ft_stdlib.h"

//The Change Directory fucntion is responsible to change the directory accordin-
//gly to the path provided by the used input and passed by the ft_cd functon.
//It will return "-1" if system function chdir does not resolve successfully.
static int	change_directory(t_dl_list *head, char *path)
{
	char	old_pwd[PATH_MAX];
	int		ret;

	if (!getcwd(old_pwd, PATH_MAX))
		return (-1);
	if (ft_strcmp(path, "~") || path == NULL || !ft_strlen(path))
		path = ft_strdup(return_env_content(g_mini.env, "HOME"));
	else if (!ft_strncmp(path, "~", 1))
		path = ft_strjoin(return_env_content(g_mini.env, "HOME"), ++path);
	else if (ft_strcmp(path, "-"))
		path = ft_strdup(return_env_content(g_mini.env, "OLDPWD"));
	else
		path = ft_strdup(g_mini.argv[1]);
	ret = chdir(path);
	g_mini.env = head;
	if (ret > -1)
	{
		check_env_names("PWD", path);
		check_env_names("OLDPWD", old_pwd);
	}
	ft_free(path);
	return (ret);
}

//The cd function is reponsible to forward the path and/or arguments list
//to the change_directory function. It will be used to receive the return
//value so it can be fowarded to the internal exit status variable.
int	ft_cd(char **argv)
{
	t_dl_list	*head;
	int			ret;

	head = g_mini.env;
	ret = change_directory(head, argv[1]);
	if (ret < 0)
		error_output('d', 1, NULL);
	return (ret);
}
