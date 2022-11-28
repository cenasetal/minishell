/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:52:41 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 16:07:24 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"
#include "utilities.h"
#include "libft.h"

static int	change_directory(t_dl_list *head, char *path)
{
	char	old_pwd[PATH_MAX];
	int		ret;

	if (!getcwd(old_pwd, PATH_MAX))
		return (-1);
	if (ft_strcmp(path, "~") || path == NULL || !ft_strlen(path))
		path = ft_strdup(return_env_content(g_global.env, "HOME"));
	else if (!ft_strncmp(path, "~", 1))
		path = ft_strjoin(return_env_content(g_global.env, "HOME"), ++path);
	else if (ft_strcmp(path, "-"))
		path = ft_strdup(return_env_content(g_global.env, "OLDPWD"));
	else
		path = ft_strdup(g_global.argv[1]);
	ret = chdir(path);
	g_global.env = head;
	if (ret > -1)
	{
		check_env_names("PWD", path);
		check_env_names("OLDPWD", old_pwd);
	}
	ft_free(path);
	return (ret);
}

int	ft_cd(char **argv)
{
	t_dl_list	*head;
	int			ret;

	head = g_global.env;
	ret = change_directory(head, argv[1]);
	if (ret < 0)
		error_output('d', 1, NULL);
	return (ret);
}
