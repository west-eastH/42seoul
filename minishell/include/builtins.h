/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:29:17 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/04 15:57:49 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "env_utils.h"
# include "parser.h"

int		echo(char **cmd);
int		check_sign(char *str);
int		builtin_exit(char **cmd);
int		check_builtin(char **cmd, t_package *pack);
int		solo_builtin(t_cmd *cur, t_package *pack);
void	builtin_fd_set(int *in_fd, int *out_fd, int *std_fd);
void	check_redir(t_cmd *cur, int *std_fd, int *in_fd, int *out_fd);
int		export(char **cmd, t_package *pack);
void	print_export(t_env *head);
void	add_export(char **cmd, t_package *pack);
int		unset(char **cmd, t_package *pack);
int		pwd(void);
void	check_result(int result, t_package *pack, char *temp, char *cmd);
int		cd(char **cmd, t_package *pack);
int		print_env(t_env *head);
#endif
