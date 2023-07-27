/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:25:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/27 14:26:14 by dongseo          ###   ########.fr       */
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

void	ft_close(int cnt, int *fd[])
{
	int i = 0;
	int j = 0;
	if (cnt > 1)
	{
		while (i < cnt - 1)
		{
			j = 0;
			while (j < 2)
			{
				close(fd[i][j]);
				j++;
			}
			i++;
		}
	}
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

void	ft_perror(char *msg)
{
	perror(msg);
	exit(1);
}

int	**make_pipe(int cnt)
{
	int	i;
	int **result;
	result = (int **)malloc(sizeof(int *) * (cnt));
	if (!result)
		ft_perror("malloc error");
	i = 0;
	while (i < cnt)
	{
		result[i] = (int *)malloc(sizeof(int) * 2);
		if (!result[i])
			ft_perror("malloc error");
		i++;
	}
	return result;
}

int	main(int argc, char *argv[], char **envp)
{
	int		**fd;
	pid_t	pid;
	int		status;
	int		i;
	int j;

	if (argc < 5)
		return (0);
	fd = make_pipe(argc - 4);
	i = 0;
	while (i < argc - 3)
	{
		if (i < argc - 4)
			if (pipe(fd[i]) < 0)
				ft_perror("pipe error");
		pid = fork();
		if (pid < 0)
			ft_perror("fork error");
		else if (pid == 0 && i == 0)
			first_child(fd, argv, envp);
		else if (pid == 0 && i == argc - 4)
			last_child(fd, argv, envp, i);
		else if (pid == 0)
			middle_child(fd, argv, envp, i);
		i++;
	}
	i = 0;
	while (i < argc - 4)
	{
		j = 0;
		while (j < 2)
		{
			close(fd[i][j]);
			j++;
		}
		i++;
	}
	while (argc-- - 3)
		wait(&status);
	exit(0);
}
