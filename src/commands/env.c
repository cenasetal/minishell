/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 22:30:10 by mgueifao          #+#    #+#             */
/*   Updated: 2021/10/20 15:05:35 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

//The env function is responsible for printing the internal environmental list.
void	ft_env(t_dl_list *env)
{
	ft_lstprint(env, 'a');
}
