/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:03:56 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/05 19:58:19 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_cmds(t_info *info, t_cmd *cmd, int idx)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_print(0, 0, 0);
	else if (pid == 0)
	{
		parse_cmd(idx, info, cmd);
		if (idx == 0)
			exec_first(info, cmd);
		else if (idx == info->cmd_nums - 1)
			exec_last(info, cmd);
		else
			exec_mid(info, cmd);
	}
	else if (idx != info->cmd_nums - 1)
	{
		if (idx != 0 && close(info->prev_fd) == -1)
			error_print(0, 0, 0);
		info->prev_fd = info->fds[0];
		if (close(info->fds[1]) == -1 || pipe(info->fds) == -1)
			error_print(0, info, cmd);
	}
	else
		info->last_child = pid;
}

void	exec_first(t_info *info, t_cmd *cmd)
{
	int		infile_fd;
	int		r_fd;
	int		w_fd;

	if (close(info->fds[0]) == -1)
		error_print(0, 0, 0);
	infile_fd = open(info->infile, O_RDONLY);
	if (infile_fd == -1)
		error_print(0, 0, 0);
	r_fd = dup2(infile_fd, STDIN_FILENO);
	w_fd = dup2(info->fds[1], STDOUT_FILENO);
	if (r_fd == -1 || w_fd == -1)
		error_print(0, 0, 0);
	if (close(info->fds[1]) == -1 || close(infile_fd) == -1)
		error_print(0, 0, 0);
	execve(cmd->cmd_path, cmd->cmds, 0);
}

void	exec_last(t_info *info, t_cmd *cmd)
{
	int		outfile_fd;
	int		r_fd;
	int		w_fd;

	outfile_fd = open(info->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		error_print(0, 0, 0);
	r_fd = dup2(info->prev_fd, STDIN_FILENO);
	w_fd = dup2(outfile_fd, STDOUT_FILENO);
	if (r_fd == -1 || w_fd == -1)
		error_print(0, 0, 0);
	if (close(outfile_fd) == -1)
		error_print(0, 0, 0);
	if (execve(cmd->cmd_path, cmd->cmds, 0))
		error_print(COMMAND_ERROR, 0, cmd);
}

void	exec_mid(t_info *info, t_cmd *cmd)
{
	int		r_fd;
	int		w_fd;

	r_fd = dup2(info->prev_fd, STDIN_FILENO);
	w_fd = dup2(info->fds[1], STDOUT_FILENO);
	if (r_fd == -1 || w_fd == -1)
		error_print(0, 0, 0);
	if (close(info->fds[1]) == -1 || close(info->prev_fd) == -1)
		error_print(0, 0, 0);
	execve(cmd->cmd_path, cmd->cmds, 0);
}

void	wait_n_exit(t_info *info)
{
	pid_t	tmp_pid;
	int		status;
	int		exit_status;

	tmp_pid = 0;
	while (info->cmd_nums--)
	{
		tmp_pid = waitpid(-1, &status, 0);
		if (tmp_pid == info->last_child)
			exit_status = WEXITSTATUS(status);
	}
	if (info->limiter)
		unlink(info->infile);
	exit(exit_status);
}
