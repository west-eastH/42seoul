/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:04:11 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/27 21:31:46 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# define INFILE_ERROR 1
# define COMMAND_ERROR 2

typedef struct s_cmd
{
	char	*cmd_path;
	char	**cmds;
}	t_cmd;

typedef struct s_info
{
	char	**path;
	char	**cmd_argv;
	char	*infile;
	char	*outfile;
	char	*limiter;
	int		cmd_nums;
	int		fds[2];
	int		prev_fd;
	pid_t	last_child;
}	t_info;

void	error_print(int flag, t_info *info, t_cmd *cmd);
void	check_input(int argc, char **argv, char **envp, t_info *info);
void	execute_cmds(t_info *info, t_cmd *cmd, int idx);
void	parse_cmd(int idx, t_info *info, t_cmd *cmd);
void	exec_first(t_info *info, t_cmd *cmd);
void	exec_last(t_info *info, t_cmd *cmd);
void	exec_mid(t_info *info, t_cmd *cmd);
void	wait_n_exit(t_info *info);
void	check_heredoc(int argc, char **argv, char **envp, t_info *info);

#endif
