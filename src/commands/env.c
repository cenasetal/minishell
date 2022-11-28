/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:54:08 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 11:54:11 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//The env function is responsible for printing the internal environmental list.
void	ft_env(t_dl_list *env)
{
	ft_lstprint(env, 'a');
}
