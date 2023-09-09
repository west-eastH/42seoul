/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:12:23 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/07 14:15:30 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "builtins.h"
# include "parser.h"

void	executor(t_cmd *cmds_head, t_package *pack, int idx);
int		open_files(t_cmd *cmd, t_package *pack);
int		open_check(t_redir *temp);
void	fd_open(t_redir *temp);
char	**make_envp(t_package *pack);
pid_t	execute_cmds(t_cmd *cur, int *fds, int idx, t_package *pack);
void	set_fd(t_cmd *cur, int fds[2], int tmp_fds[3]);
void	free_cmd(t_cmd	**head);
int		ft_wait(int idx, t_cmd *cmds_head, int last_pid);
void	unlink_files(t_cmd *head);
void	ft_perror(char *str, int exit_num);
void	exec_handler(int sig);

char	*itoa(int n);
int		do_heredoc(t_redir *temp, char *f_name, int len, t_package *pack);
void	handler_heredoc(int sig);
int		here_doc_open(t_redir *temp, t_package *pack);
void	heredoc_expander(int infile, char *line, t_package *pack);
void	write_heredoc(t_redir *temp, t_package *pack, int fd, int len);
int		detact_exitcode(int temp);

void	do_child(t_cmd *cur, t_package *pack, int *fds, int *tmp_fds);
void	do_parent(int *fds, int *tmp_fds, int idx);

#endif
