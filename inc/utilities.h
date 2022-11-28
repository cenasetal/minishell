/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 04:15:40 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 17:12:30 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "libft.h"

# include "parser.h"

# define CHAR_UNHANDLED 1
# define QUOTES_OPEN 2
# define MAX_FD 256

int			error_output(char type, int i, char *str);

int			env_sorted(void);

int			check_env_names(char *name, char *content);
void		print_env_content(t_dl_list *lst, char *name, char free_name);
char		*return_env_content(t_dl_list *lst, char *name);
char		*get_name(char *str, char c);
t_dl_list	*get_env(char **env);

void		free_list_nodes(t_dl_list *lst);
void		free_argv(void);
void		free_dl_list(t_dl_list *lst);
void		delete_temp(char *path);
void		free_table(char **table);

void		signal_handler(int signal);
void		clean_processes(void);
void		re_init(void);
void		check_and_or_flag(t_cmd *cmd, t_tree *t, int i);
void		tree_loop(t_tree *t, int i);
void		create_hdoc_and_pid_arrays(void);
void		exit_loop(void);
int			dup_init_and_close(char type);

void		exit_fork(void);

int			file_input(t_list *input, t_list *heredoc, t_list *in);
int			file_output(t_list *output, t_list *append, t_list *final_output);

int			screening_one(char **argv);
void		cmd_selector(char **argv);
int			cmd_identifier(char **argv);

char		*temp_path(char *filename, char *home);
void		check_heredoc(t_tree *t);

#endif
