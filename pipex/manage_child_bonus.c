/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_child_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:18:39 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/01 18:03:57 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child(int *fd[], char *argv[], char **envp)
{
	int		in_fd;
	char	**cmd;

	close(fd[0][0]);
	in_fd = open(argv[1], O_RDONLY);
	if (in_fd < 0)
		ft_perror("file open error");
	cmd = ft_split(argv[2], ' ');
	dup2(in_fd, 0);
	dup2(fd[0][1], 1);
	close(in_fd);
	close(fd[0][1]);
	if (argv[2][0] == '/')
		if (execve(cmd[0], cmd, envp) < 0)
			ft_perror("execve error");
	ft_execve(cmd, envp);
}

void	middle_child(int *fd[], char *argv[], char **envp, int i)
{
	char	**cmd;

	ft_close(i, fd);
	close(fd[i - 1][1]);
	close(fd[i][0]);
	cmd = ft_split(argv[i + 2], ' ');
	dup2(fd[i - 1][0], 0);
	close(fd[i - 1][0]);
	dup2(fd[i][1], 1);
	close(fd[i][1]);
	if (argv[i + 2][0] == '/')
		if (execve(cmd[0], cmd, envp) < 0)
			ft_perror("execve error");
	ft_execve(cmd, envp);
}

void	last_child(int *fd[], char *argv[], char **envp, t_idx *idx)
{
	int		out;
	char	**cmd;

	ft_close(idx->i, fd);
	close(fd[idx->i - 1][1]);
	cmd = ft_split(argv[idx->i + 2], ' ');
	if (idx->is_here_doc == 1)
		out = open(argv[idx->i + 3], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		out = open(argv[idx->i + 3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out < 0)
		ft_perror("file open error");
	dup2(fd[idx->i - 1][0], 0);
	close(fd[idx->i - 1][0]);
	dup2(out, 1);
	close(out);
	if (argv[idx->i + 2][0] == '/')
		if (execve(cmd[0], cmd, envp) < 0)
			ft_perror("execve error");
	ft_execve(cmd, envp);
}

void	ft_execve(char **cmd, char **envp)
{
	char	**split;
	int		i;
	char	*result;
	char	*path;

	path = set_path(envp);
	split = ft_split(path + 5, ':');
	i = 0;
	while (split[i])
	{
		result = ft_cmdjoin(split[i], cmd[0]);
		if (access(result, X_OK) == 0)
		{
			if (execve(result, cmd, envp) < 0)
				ft_perror("execve error");
		}
		free(result);
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
	ft_perror("command error");
}
