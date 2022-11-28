/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:41 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 23:21:07 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#include "libft.h"

#include "minishell.h"
#include "parser.h"

static char	*replace(char *s1, const char *s2, int pos, int len)
{
	char	*t1;
	char	*t2;
	char	*mask;
	int		i;

	t1 = ft_substr(s1, 0, pos);
	mask = ft_strdup(s2);
	i = -1;
	if (len & INT_MIN)
		while (mask[++i])
			mask[i] |= 0x80;
	t2 = ft_strjoin(t1, mask);
	ft_free(mask);
	ft_free(t1);
	t1 = ft_strjoin(t2, s1 + pos + (len & INT_MAX));
	ft_free(t2);
	return (t1);
}

static int	expand1(char **str, int start, t_cmd *cmd, int i)
{
	char	*s;
	char	*big;
	char	*tmp;

	i = start - 1;
	s = *str;
	if ((s[i + 1] & 0x7F) == '?')
		cmd->cmd_flags |= 2;
	if ((s[i + 1] & 0x7F) == '?')
		return (0);
	while (ft_isalnum((s[++i] & 0x7F)) || (s[i] & 0x7F) == '_')
		;
	i -= start;
	if (!i)
		return (0);
	tmp = ft_substr(s, start, i);
	unmask_str(tmp);
	big = ft_listget_dl(tmp, g_global.env);
	ft_free(tmp);
	if (!big)
		return (0);
	*str = replace(s, big, start - 1, (i + 1) + ((s[start] & 0x80) * 16777216));
	i = ft_abs(i - ft_strlen(big));
	ft_free(s);
	return (i);
}

static char	*expand_cmd(char *s, t_cmd *cmd)
{
	int	i;

	i = -2;
	if (!s)
		return (NULL);
	while (++i && s[(++i) >> 1])
	{
		(s[i >> 1] == '\'') && (i ^= 1);
		if (i & 1)
			continue ;
		if ((s[i >> 1] & 0x7F) == '$')
		{
			if ((s[(i >> 1) + 1] & 0x7F) == '?')
				i += (expand_question(&s, (i >> 1), 0) << 1);
			else
				i += (expand1(&s, (i >> 1) + 1, cmd, 0) << 1);
		}
	}
	return (s);
}

int	expand(t_tree *t)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)t->content;
	if (cmd)
	{
		cmd->line = expand_cmd(cmd->line, cmd);
		if (!cmd->line)
			return (0);
	}
	i = 0;
	while (i < t->lcount)
		if (!expand(t->leaves[i++]))
			return (0);
	return (1);
}
