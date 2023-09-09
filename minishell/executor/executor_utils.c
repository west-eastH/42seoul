/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:25:42 by dongseo           #+#    #+#             */
/*   Updated: 2023/09/09 11:19:31 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

void	fd_open(t_redir *temp)
{
	if (temp->type == L_LESSER)
		temp->fd = open(temp->filename[1], O_RDONLY);
	else if (temp->type == L_GREATER)
		temp->fd = open(temp->filename[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (temp->type == L_D_GREATER)
		temp->fd = open(temp->filename[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
}

int	ft_wait(int idx, t_cmd *cmds_head, int last_pid)
{
	int		status;
	int		exit_num;

	exit_num = g_exit_status;
	while (idx--)
	{
		if (waitpid(-1, &status, 0) == last_pid)
		{
			if (WIFSIGNALED(status))
				exit_num = WTERMSIG(status) + 128;
			else if (WIFEXITED(status))
				exit_num = WEXITSTATUS(status);
		}
	}
	unlink_files(cmds_head);
	return (exit_num);
}

void	free_cmd(t_cmd	**head)
{
	t_cmd	*temp;
	t_redir	*redir;
	int		idx;

	while (*head)
	{
		temp = *head;
		idx = 0;
		while (temp->cmd_args && temp->cmd_args[idx])
		{
			free(temp->cmd_args[idx]);
			idx++;
		}
		free(temp->cmd_args);
		while (temp->redirection)
		{
			redir = temp->redirection;
			free_strings(redir->filename);
			temp->redirection = temp->redirection->next;
			free(redir);
		}
		*head = temp->next;
		free(temp);
	}
}

void	ft_perror(char *str, int exit_num)
{
	if (exit_num == 126)
		printf("minishell😎: %s: is a directory\n", str);
	else if (exit_num == 127)
		printf("minishell😎: %s: command not found\n", str);
	else if (exit_num == 128)
	{
		printf("minishell😎: %s: No such file or directory\n", str);
		exit_num--;
	}
	else
		perror(str);
	exit(exit_num);
}
