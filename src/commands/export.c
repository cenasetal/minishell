/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 22:30:22 by mgueifao          #+#    #+#             */
/*   Updated: 2021/10/20 15:07:41 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"

#include "ft_string.h"

//The Find Char function returns where is the char that we provided in a string.
//It will return the full length of the string if no char is found.
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

//The simple export call will list all our internal environmental variable,
//ordered alphabetically.
int	ft_export(char **argv)
{
	t_dl_list	*head;
	t_dl_list	*temp;
	char		*content[2];
	char		*arg;

	head = g_mini.env;
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
		ft_lstadd_back_dl(&g_mini.env, temp);
	}
	g_mini.env = head;
	return (1);
}
