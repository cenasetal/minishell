/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:42:21 by mgueifao          #+#    #+#             */
/*   Updated: 2022/02/10 01:04:53 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>

#include "parser.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "ft_list.h"

static void	find_bound(int *start, int *end, char *s, int i)
{
	*start = 0;
	*end = 1;
	while (i - *start > 0 && !ft_isspecial(s[i - *start]))
		*start = *start + 1;
	while (s[i + *end] && !ft_isspecial(s[i + *end]))
		*end = *end + 1;
	if (ft_isspecial(s[i - *start]))
		*start = *start - 1;
	if (ft_isspecial(s[i + *end]))
		*end = *end - 1;
}

static int	checkexp(char **ss, char *dir, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if ((*s != '*' && ft_strncmp(ss[i], dir + j, ft_strlen(ss[i])))
		|| (*s == '*' && *dir == '.'))
		return (0);
	while (ss[i] && ft_strlen(dir) > (size_t) j)
	{
		if (!ft_strncmp(ss[i], dir + j, ft_strlen(ss[i])))
			j += ft_strlen(ss[i++]);
		else
			j++;
	}
	return (!ss[i] && (s[ft_strlen(s) - 1] == '*' || (int)ft_strlen(dir) == j));
}

static t_list	*cmpfiles(char **str, char *s, int norm)
{
	DIR				*dir;
	struct dirent	*d;
	t_list			*ret;

	dir = opendir(".");
	ret = NULL;
	if (dir)
	{
		d = readdir(dir);
		while (d != NULL)
		{
			if (checkexp(str, d->d_name, s))
				ft_lstadd_back(&ret, ft_lstnew(ft_strdup(d->d_name)));
			d = readdir(dir);
		}
		closedir(dir);
	}
	while (str[++norm])
		ft_free(str[norm]);
	return (ret);
}

static char	*lstjoin(t_list *l)
{
	char	*ret;
	char	*aux;
	t_list	*tmp;

	tmp = l;
	ret = ft_calloc(1, 1);
	lstsort(&l);
	while (tmp)
	{
		aux = ft_strjoin(ret, tmp->content);
		ft_free(ret);
		ret = ft_strjoin(aux, " ");
		ft_free(aux);
		tmp = tmp->next;
	}
	ft_lstclear(&l, ft_free);
	return (ret);
}

int	wild(int i, char **s, t_cmd *cmd, int norm)
{
	int		start;
	int		end;
	char	*wild;
	char	**strs;
	char	*list;

	find_bound(&start, &end, *s, i);
	wild = ft_substr(*s, i - start, start + end + 1);
	strs = ft_split(wild, '*');
	list = lstjoin(cmpfiles(strs, wild, norm));
	ft_free(wild);
	norm = !!ft_strlen(list);
	if (norm)
	{
		wild = ft_substr(*s, 0, i - start);
		*strs = ft_strjoin(wild, list);
		ft_free(wild);
		wild = ft_strjoin(*strs, *s + i + end + 1);
		ft_free(*s);
		(1 && (*s = wild) && (cmd->line = *s));
		ft_free(*strs);
	}
	ft_free(list);
	ft_free(strs);
	return (((i - start - 1) * norm) + (i * !norm));
}
