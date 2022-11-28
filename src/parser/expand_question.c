/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_question.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 23:07:28 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 23:14:47 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include <limits.h>

static char	*replace_question(char *s1, const char *s2, int pos, int len)
{
	char	*t1;
	char	*t2;
	char	*mask;
	int		i;

	t1 = ft_substr(s1, 0, pos - 1);
	mask = ft_strdup(s2);
	i = -1;
	if (len & INT_MIN)
		while (mask[++i])
			mask[i] |= 0x80;
	t2 = ft_strjoin(t1, mask);
	ft_free(mask);
	ft_free(t1);
	t1 = ft_strjoin(t2, s1 + pos + 1);
	ft_free(t2);
	return (t1);
}

int	expand_question(char **str, int start, int i)
{
	char	*s;
	char	*big;


	i = 2;
	s = *str;
	big = ft_itoa(g_global.exit_status);
	if (!big)
		return (0);
	*str = replace_question(s, big, start + 1, i + 1);
	i = ft_abs(i - ft_strlen(big));
	ft_free(s);
	ft_free(big);
	if (i == 1)
		return (0);
	return (i);
}
