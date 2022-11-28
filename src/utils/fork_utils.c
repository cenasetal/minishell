/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:59:15 by fferreir          #+#    #+#             */
/*   Updated: 2021/11/25 16:08:31 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_stdlib.h"

#include "minishell.h"

//free_dl_list(g_mini.env);
void	exit_fork(void)
{
	ft_free(g_mini.input);
	exit(0);
}
