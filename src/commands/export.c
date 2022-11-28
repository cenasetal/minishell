/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:54:56 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 16:09:41 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"
#include "libft.h"

static int	find_char(char *s1, char c)
{
	int	x;

	x = 0;
	if (!s1)
		return (x);
	while (s1[x] && s1[x] != c)
		x++;
	return (x);
}

int	ft_export(char **argv)
{
	t_dl_list	*head;
	t_dl_list	*temp;
	char		*content[2];
	char		*arg;

	head = g_global.env;
	arg = argv[1];
	content[0] = get_name(arg, '=');
	if (!content[0])
		return (env_sorted());
	if (!find_char(arg, '='))
		return (0);
	content[1] = ft_substr(arg, find_char(arg, '=') + 1, ft_strlen(arg));
	if (!check_env_names(content[0], content[1]))
	{
		temp = ft_lstnew_dl(content);
		ft_lstadd_back_dl(&g_global.env, temp);
	}
	g_global.env = head;
	return (1);
}
