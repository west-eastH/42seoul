/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:12:23 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/28 17:00:49 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "env_utils.h"
# include "parser.h"

int		open_files(t_cmd *cmd);
int		check_builtin(char **cmd, int flag);
int		export(char **cmd);
int		print_env(t_env *head);
int		unset(char **cmd);
int		pwd	(void);
int		cd(char **cmd);
int		echo(char **cmd);
int		builtin_exit(char **cmd);
void	here_doc_open(t_redir *temp);
#endif
