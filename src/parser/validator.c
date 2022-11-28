/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:37 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 16:04:26 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static int	isempty(const char *str)
{
	int	i;

	i = 0;
	while (str && ft_isspace(str[i]))
		i++;
	return (str && !str[i]);
}

static int	check_qparen(const char *str, int i)
{
	char	q;
	char	text;

	q = 0;
	text = 0;
	while (i != -2 && str[++i])
	{
		(str[i] == '\'') && !(q & 2) && (q ^= 1);
		(str[i] == '\"') && !(q & 1) && (q ^= 2);
		if ((q || ft_isspace(str[i])))
			continue ;
		if (str[i] == '(')
			i = check_qparen(str, i);
		else if (str[i] == ')' && text)
			return (i);
		else if (str[i] == ')')
			return (-2);
		else
			text++;
	}
	if (q)
		return (-2);
	return (i);
}

static int	check_ops(const char *str, char q, char text, int i)
{
	while (str[++i])
	{
		(str[i] == '\'') && !(q & 2) && (text = 1) && (q ^= 1);
		(str[i] == '\"') && !(q & 1) && (text = 1) && (q ^= 2);
		if (q & 3 || ft_isspace(str[i]))
			continue ;
		if (((str[i] == '&' && str[i + 1] == '&')
				|| (str[i] == '|' && str[i + 1] == '|') || (str[i] == ';')))
		{
			if ((!text && q != 8) || (text && q == 8))
				return (0);
			((str[i] != ';') && ++i && (q == -1)) || (text = 0) || (q &= 3);
		}
		else if (str[i] == ')' && ((text && !(q == 8)) || (!text && (q == 8))))
			(text || !text) && (q = 8)
				&& (text = 0);
		else if (str[i] == '(' && !text && !(q == 8))
			q = 4;
		else if (str[i] == '(' || str[i] == ')')
			return (0);
		else
			text = 1;
	}
	return ((text && q != 8) || (!text && q == 8));
}

static int	check_lvls(const char *str, int i)
{
	char	q;
	char	ao;

	q = 0;
	ao = 0;
	while (i != -2 && str[++i])
	{
		(str[i] == '\'') && !(q & 2) && (q ^= 1);
		(str[i] == '\"') && !(q & 1) && (q ^= 2);
		if ((q || ft_isspace(str[i])))
			continue ;
		if (str[i] == '(')
			i = check_qparen(str, i);
		else if (str[i] == ')')
			return (i);
		else
			((str[i] == '&') && (str[i + 1] == '&') && !ao && (ao = 1))
			|| ((str[i] == '|') && (str[i + 1] == '|') && !ao && (ao = 2))
			|| ((str[i] == '&') && (str[i + 1] == '&') && ao == 2 && (i = -2))
			|| ((str[i] == '|') && (str[i + 1] == '|') && ao == 1 && (i = -2));
	}
	return (i);
}

t_commands	*validate(const char *str)
{
	t_commands	*cmd;

	cmd = ft_calloc(1, sizeof(t_commands));
	if (!cmd)
		return (NULL);
	if (!str)
		cmd->error = 404;
	else if (isempty(str))
		return (cmd);
	if (check_qparen(str, -1) != (int)ft_strlen(str))
		cmd->error = 500;
	else if (!check_ops(str, 0, 0, -1))
		cmd->error = 501;
	else if (check_lvls(str, -1) != (int)ft_strlen(str))
		cmd->error = 502;
	return (cmd);
}
