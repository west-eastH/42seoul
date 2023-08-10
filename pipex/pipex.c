/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:25:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/10 13:56:53 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_perror(char *msg)
{
	perror(msg);
	exit(1);
}

int	ft_wait(int argc, int **fd, int last_pid)
{
	int	status;
	int	exit_num;

	ft_close(argc - 3, fd);
	while (argc-- - 3)
	{
		if (waitpid(-1, &status, 0) == last_pid)
		{
			if (WIFSIGNALED(status))
				exit_num = WTERMSIG(status);
			else if (WIFEXITED(status))
				exit_num = WEXITSTATUS(status);
		}
	}
	exit(exit_num);
}

int	main(int argc, char *argv[], char **envp)
{
	int		**fd;
	pid_t	pid;
	int		i;

	if (argc != 5)
		ft_perror("argc");
	fd = make_pipe(argc - 4);
	i = 0;
	while (i < argc - 3)
	{
		if (i < argc - 4)
			if (pipe(fd[i]) < 0)
				ft_perror("pipe");
		pid = fork();
		if (pid < 0)
			ft_perror("fork");
		else if (pid == 0 && i == 0)
			first_child(fd, argv, envp);
		else if (pid == 0 && i == argc - 4)
			last_child(fd, argv, envp, i);
		else if (pid == 0)
			middle_child(fd, argv, envp, i);
		i++;
	}
	ft_wait(argc, fd, pid);
}
