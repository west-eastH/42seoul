/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:19:13 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/07 14:15:20 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd(t_cmd *cur, int *fds, int *tmp_fds)
{
	if (cur->infile)
	{
		tmp_fds[0] = open(cur->infile->filename[1], O_RDONLY);
		if (tmp_fds[0] == -1)
			ft_perror(cur->infile->filename[1], 1);
	}
	else
		tmp_fds[0] = fds[2];
	if (cur->outfile)
	{
		if (cur->outfile->type == L_D_GREATER)
			tmp_fds[1] = open(cur->outfile->filename[1], \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			tmp_fds[1] = open(cur->outfile->filename[1], \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (tmp_fds[0] == -1)
			ft_perror(cur->infile->filename[1], 1);
	}
	else if (cur->next)
		tmp_fds[1] = fds[1];
}

void	do_child(t_cmd *cur, t_package *pack, int *fds, int *tmp_fds)
{
	if (tmp_fds[0] != 0)
	{
		dup2(tmp_fds[0], STDIN_FILENO);
		close(tmp_fds[0]);
	}
	if (tmp_fds[1] != 1)
	{
		dup2(tmp_fds[1], STDOUT_FILENO);
		close(tmp_fds[1]);
	}
	if (fds[0])
		close(fds[0]);
	if (fds[1] != 1)
		close(fds[1]);
	if (check_builtin(cur->cmd_args, pack))
		exit(0);
	else
		pipe_exec(cur, pack);
	exit(0);
}

void	do_parent(int *fds, int *tmp_fds, int idx)
{
	if (tmp_fds[0] > 2)
		close(tmp_fds[0]);
	if (tmp_fds[1] > 2)
		close(tmp_fds[1]);
	if (idx != 0 && fds[2])
		close(fds[2]);
	if (fds[1] != 1)
		close(fds[1]);
	fds[2] = fds[0];
}

void	unlink_files(t_cmd *head)
{
	t_redir	*redir;

	while (head)
	{
		redir = head->redirection;
		while (redir)
		{
			if (redir->type == L_D_LESSER)
				unlink(redir->filename[1]);
			redir = redir->next;
		}
		head = head->next;
	}
}
