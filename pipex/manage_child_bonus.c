/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_child_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:18:39 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/21 20:03:16 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child(int *fd[], char *argv[], char **envp)
{
	int		in_fd;
	char	**cmd;

	file_close(fd[0][0]);
	in_fd = open(argv[1], O_RDONLY);
	if (in_fd < 0)
		ft_perror("file open");
	if (is_group(argv[2]))
	{
		cmd = ft_split(argv[2], '"');
		cmd[0] = ft_strtrim(cmd[0], " ");
	}
	else
		cmd = ft_split(argv[2], ' ');
	ft_dup2(in_fd, 0);
	ft_dup2(fd[0][1], 1);
	file_close(in_fd);
	file_close(fd[0][1]);
	if (argv[2][0] == '/')
		if (execve(cmd[0], cmd, envp) < 0)
			ft_perror("execve");
	ft_execve(cmd, envp);
}

void	middle_child(int *fd[], char *argv[], char **envp, int i)
{
	char	**cmd;

	ft_close(i, fd);
	file_close(fd[i - 1][1]);
	file_close(fd[i][0]);
	if (is_group(argv[i + 2]))
	{
		cmd = ft_split(argv[i + 2], '"');
		cmd[0] = ft_strtrim(cmd[0], " ");
	}
	else
		cmd = ft_split(argv[i + 2], ' ');
	ft_dup2(fd[i - 1][0], 0);
	file_close(fd[i - 1][0]);
	ft_dup2(fd[i][1], 1);
	file_close(fd[i][1]);
	if (argv[i + 2][0] == '/')
		if (execve(cmd[0], cmd, envp) < 0)
			ft_perror("execve");
	ft_execve(cmd, envp);
}

void	last_child(int *fd[], char *argv[], char **envp, t_idx *idx)
{
	int		out;
	char	**cmd;

	ft_close(idx->i, fd);
	file_close(fd[idx->i - 1][1]);
	if (is_group(argv[idx->i + 2]))
	{
		cmd = ft_split(argv[idx->i + 2], '"');
		cmd[0] = ft_strtrim(cmd[0], " ");
	}
	else
		cmd = ft_split(argv[idx->i + 2], ' ');
	out = file_open(argv[idx->i + 3], idx->is_here_doc);
	if (out < 0)
		ft_perror("file open");
	ft_dup2(fd[idx->i - 1][0], 0);
	file_close(fd[idx->i - 1][0]);
	ft_dup2(out, 1);
	file_close(out);
	if (argv[idx->i + 2][0] == '/')
		if (execve(cmd[0], cmd, envp) < 0)
			ft_perror("execve");
	ft_execve(cmd, envp);
}

int	is_group(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

void	ft_execve(char **cmd, char **envp)
{
	char	**split;
	int		i;
	char	*result;
	char	*path;

	if (cmd[0] == NULL || !cmd)
		command_error(cmd);
	path = set_path(envp);
	split = ft_split(path + 5, ':');
	i = 0;
	while (split[i])
	{
		result = ft_cmdjoin(split[i], cmd[0]);
		if (access(result, X_OK) == 0)
		{
			if (execve(result, cmd, envp) < 0)
				ft_perror("execve");
		}
		free(result);
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
	command_error(cmd);
}
