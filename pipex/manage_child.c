/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:18:39 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/30 20:02:25 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		execve(cmd[0], cmd, envp);
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
		execve(cmd[0], cmd, envp);
	ft_execve(cmd, envp);
}

void	last_child(int *fd[], char *argv[], char **envp, int i)
{
	int		out;
	char	**cmd;

	ft_close(i, fd);
	close(fd[i - 1][1]);
	cmd = ft_split(argv[i + 2], ' ');
	out = open(argv[i + 3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out < 0)
		ft_perror("file open error");
	dup2(fd[i - 1][0], 0);
	close(fd[i - 1][0]);
	dup2(out, 1);
	close(out);
	if (argv[i + 2][0] == '/')
		execve(cmd[0], cmd, envp);
	ft_execve(cmd, envp);
}
