/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:25:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/27 12:49:58 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int fd[2], char *argv[], char **envp, char *buffer)
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
	close(in_fd);
	close(fd[1]);
	if (argv[2][0] == '/')
		execve(cmd[0], cmd, envp);
	ft_execve(cmd, envp);
}

void	second_child(int fd[2], char *argv[], char **envp)
{
	int		out;
	char	**cmd;

	close(fd[1]);
	cmd = ft_split(argv[3], ' ');
	out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out < 0)
		ft_perror("file open error");
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(out, 1);
	close(out);
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
	int		*fd[2];
	pid_t	pid;
	int		status;
	int		i;
	char	*buffer;

	if (argc < 5)
		return (0);
	i = argc - 3;
	if (pipe(fd) < 0)
		ft_perror("pipe error");
	while (i > 0)
	{
		pid = fork();
		if (pid < 0)
			ft_perror("fork error");
		else if (pid == 0 && i == (argc - 3))
			first_child(fd, argv, envp, buffer);
		else if (pid == 0 && i == 1)
			last_child();
		else
			middle_child();
		i--;
	}
	close(fd[0]);
	close(fd[1]);
	while (argc-- - 3)
		wait(&status);
	exit(0);
}
