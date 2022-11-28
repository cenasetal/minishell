/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:06:16 by fferreir          #+#    #+#             */
/*   Updated: 2022/02/09 02:21:27 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_stdlib.h"
#include "ft_conv.h"

#include "utilities.h"
#include "minishell.h"

void	create_hdoc_and_pid_arrays(void)
{
	int	i;

	i = -1;
	g_mini.hdoc_files = ft_malloc(sizeof(char **) * (FD_MAX + 1));
	while (++i < FD_MAX)
		g_mini.hdoc_files[i] = ft_itoa(i);
	g_mini.hdoc_files[i] = NULL;
	g_mini.pid_lst = ft_malloc(sizeof(int *) * (CHILD_MAX + 1));
	i = -1;
	while (++i < CHILD_MAX)
		g_mini.pid_lst[i] = -1;
	g_mini.pid_lst[i] = '\0';
}

void	exit_loop(void)
{
	int	i;

	free_dl_list(g_mini.env);
	i = -1;
	while (++i < FD_MAX)
		ft_free(g_mini.hdoc_files[i]);
	ft_free(g_mini.hdoc_files);
	ft_free(g_mini.pid_lst);
	exit(0);
}
