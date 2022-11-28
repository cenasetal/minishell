/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgueifao <mgueifao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:03:59 by mgueifao          #+#    #+#             */
/*   Updated: 2021/11/16 02:16:23 by mgueifao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdlib.h"

#include "parser.h"
#include "utilities.h"

int	unmask_str(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		(str[i] &= 0x7F);
		!str[i] && (str[i] = '$');
	}
	return (1);
}

int	unmask(t_tree *t)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)t->content;
	i = -1;
	if (cmd && cmd->line)
		unmask_str(cmd->line);
	if (cmd && cmd->cmd)
		while (cmd->cmd[++i])
			if (!unmask_str(cmd->cmd[i]))
				return (0);
	i = 0;
	while (i < t->lcount)
		if (!unmask(t->leafs[i++]))
			return (0);
	return (1);
}

static char	*rem_q(char *str, int count)
{
	char	*ret;
	int		p1;
	int		p2;

	ret = ft_calloc(ft_strlen(str) - count + 1, 1);
	p1 = -1;
	p2 = -1;
	while (str[++p1])
		if (!ft_strchr("\\\"\'", str[p1]))
			ret[++p2] = str[p1];
	ft_free(str);
	return (ret);
}

/**
 * q:
 *	S : single quotes
 *	D : double quotes
 *	Q : skip escape
 *	V : inside variable
 *
 * Toogle single quotes
 * Toogle double quotes
 * Escape next char
 * Enter var
 */
char	*proc_q(char *str, t_commands *cmd)
{
	char	q;
	int		count;
	char	*c;

	q = 0;
	count = 0;
	c = str - 1;
	while (*++c)
	{
		q &= ~Q;
		(*c == '\'') && !(q & D) && ((q ^= S | Q) || 1) && (count++);
		(*c == '\"') && !(q & S) && ((q ^= D | Q) || 1) && (count++);
		(*c == '$') && !(q & S) && (q |= V);
		(ft_strchr(" \'\"\\;&|", *c)) && (q &= ~V);
		(*c == '$') && (q & S) && (*c = 0x80);
		(*c == '\\') && !(q & S) && (((ft_strchr("\\\"", *(c + 1))) && (c++)
			&& (++count) && (*c |= 0x80))
			|| (('$' == *(c + 1)) && (c++) && (*c = 0x80) && (++count)));
		(*c & 0x7F) && (q & (S | D)) && !(q & Q) && (*c |= 0x80);
	}
	if (q & (S | D))
		cmd->error = QUOTES_OPEN;
	return (rem_q(str, count));
}
