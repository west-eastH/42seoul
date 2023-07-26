/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:25:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/26 16:03:39 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int fd[2], char *argv[], char **envp)
{
	int		in_fd;
	char	**cmd;

	close(fd[0]);
	in_fd = open(argv[1], O_RDONLY);
	if (in_fd < 0)
		ft_perror("file open error");
	cmd = ft_split(argv[2], ' ');
	dup2(in_fd, 0);
	dup2(fd[1], 1);
	if (argv[2][0] == '/')
		execve(cmd[0], cmd, envp);
	ft_execve(cmd, envp);
}

void	parent_process(int fd[2], char *argv[], char **envp, pid_t pid)
{
	int		status;
	int		out;
	char	**cmd;

	waitpid(pid, &status, 0);
	close(fd[1]);
	cmd = ft_split(argv[3], ' ');
	out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd[0], 0);
	dup2(out, 1);
	cmd = ft_split(argv[3], ' ');
	if (argv[3][0] == '/')
		execve(cmd[0], cmd, envp);
	ft_execve(cmd, envp);
}

void	ft_perror(char *msg)
{
	perror(msg);
	exit(1);
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		return (0);
	if (pipe(fd) < 0)
		ft_perror("pipe error");
	pid = fork();
	if (pid < 0)
		ft_perror("fork error");
	else if (pid == 0)
		child_process(fd, argv, envp);
	else
		parent_process(fd, argv, envp, pid);
	exit(0);
}
