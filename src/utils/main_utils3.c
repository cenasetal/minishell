/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:36 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 13:02:45 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utilities.h"
#include "minishell.h"

void	create_hdoc_and_pid_arrays(void)
{
	int	i;

	i = -1;
	g_global.hdoc_files = malloc(sizeof(char **) * (FD_MAX + 1));
	while (++i < FD_MAX)
		g_global.hdoc_files[i] = ft_itoa(i);
	g_global.hdoc_files[i] = NULL;
	g_global.pid_lst = malloc(sizeof(int *) * (CHILD_MAX + 1));
	i = -1;
	while (++i < CHILD_MAX)
		g_global.pid_lst[i] = -1;
	g_global.pid_lst[i] = '\0';
}

void	exit_loop(void)
{
	int	i;

	free_dl_list(g_global.env);
	i = -1;
	while (++i < FD_MAX)
		ft_free(g_global.hdoc_files[i]);
	ft_free(g_global.hdoc_files);
	ft_free(g_global.pid_lst);
	exit(0);
}
