/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:25:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/09 17:30:58 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_perror(char *msg)
{
	perror(msg);
	exit(1);
}

int	ft_wait(int argc, int **fd, char *argv[])
{
	int	status;
	int	last;

	last = argc - 1;
	ft_close(argc - 3, fd);
	while (argc-- - 3)
	{
		wait(&status);
	}
	if (access(argv[1], R_OK) != 0)
	{
		if (unlink(argv[last]) < 0)
			ft_perror("unlink");
	}
	exit(0);
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
	ft_wait(argc, fd, argv);
}
