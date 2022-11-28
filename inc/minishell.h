/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 04:15:52 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 12:36:27 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include "parser.h"

# ifndef CHILD_MAX
#  define CHILD_MAX 512
# endif

typedef struct s_cd
{
	t_dl_list	*tmp;
	char		*pwd;
	char		*path1;
	char		*path2;
	char		*backup;
}				t_cd;

typedef struct s_global
{
	char		**argv;
	char		*str;
	char		*temp_path;
	int			exit;
	int			nbr_arg;
	int			exit_status;
	int			first_cmd;
	int			fd[2];
	int			tmp_in;
	int			tmp_out;
	int			fd_in;
	int			fd_out;
	char		*input;
	char		*heredoc;
	char		**hdoc_files;
	int			cmd_counter;
	int			file_counter;
	int			hdoc_counter;
	int			pid_counter;
	int			and_flag;
	int			or_flag;
	int			es_flag;
	int			pid;
	int			*pid_lst;
	int			stop;
	int			saved_fd;
	t_cd		*cd;
	t_commands	*cmd;
	t_dl_list	*env;
	t_dl_list	*head;
}				t_global;

extern t_global	g_global;

#endif
