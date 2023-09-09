/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:35:51 by dongseo           #+#    #+#             */
/*   Updated: 2023/09/09 11:19:26 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig);

void	executor(t_cmd *cmds_head, t_package *pack, int idx)
{
	t_cmd	*cur;
	int		fds[3];
	pid_t	last;

	fds[0] = 0;
	fds[1] = 1;
	fds[2] = 0;
	cur = cmds_head;
	while (cur)
	{
		if (cur->next && pipe(fds) == -1)
			exit(1);
		if (!open_files(cur, pack))
		{
			if (idx == 0 && !cur->next && solo_builtin(cur, pack))
				return (free_cmd(&cmds_head));
			last = execute_cmds(cur, fds, idx++, pack);
		}
		cur = cur->next;
	}
	g_exit_status = ft_wait(idx, cmds_head, last);
	if (fds[2])
		close(fds[2]);
	free_cmd(&cmds_head);
}

int	open_files(t_cmd *cmd, t_package *pack)
{
	t_redir	*temp;

	temp = cmd->redirection;
	while (temp)
	{
		if (temp->type == L_D_LESSER || temp->type == L_LESSER)
			cmd->infile = temp;
		else if (temp->type == L_D_GREATER || temp->type == L_GREATER)
			cmd->outfile = temp;
		if (temp->type == L_D_LESSER)
		{
			if (here_doc_open(temp, pack))
				return (1);
		}
		temp = temp->next;
	}
	temp = cmd->redirection;
	return (open_check(temp));
}

int	open_check(t_redir *temp)
{
	while (temp)
	{
		if (temp->type != L_D_LESSER && temp->filename[2])
		{
			printf("minishell😎: %s: ambiguous redirect\n", temp->filename[0]);
			g_exit_status = 1;
			return (1);
		}
		fd_open(temp);
		if (temp->type != L_D_LESSER && temp->fd < 0)
		{
			if (access(temp->filename[1], F_OK) == 0)
				printf("minishell😎: %s: Permission denied\n", temp->filename[1]);
			else
				printf("minishell😎: %s: No such file or directory\n",
					temp->filename[1]);
			g_exit_status = 1;
			return (1);
		}
		if (temp->fd > 2)
			close(temp->fd);
		temp = temp->next;
	}
	return (0);
}

pid_t	execute_cmds(t_cmd *cur, int *fds, int idx, t_package *pack)
{
	int		tmp_fds[2];
	pid_t	pid;

	tmp_fds[0] = 0;
	tmp_fds[1] = 1;
	set_fd(cur, fds, tmp_fds);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, exec_handler);
	pid = fork();
	if (pid == -1)
	{
		printf("fork error\n");
		g_exit_status = 1;
	}
	if (pid == 0)
	{
		if (cur->cmd_args)
			do_child(cur, pack, fds, tmp_fds);
		exit(0);
	}
	else
		do_parent(fds, tmp_fds, idx);
	return (pid);
}
