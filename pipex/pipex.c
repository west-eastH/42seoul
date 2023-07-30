/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:25:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/30 20:02:42 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_perror(char *msg)
{
	perror(msg);
	exit(1);
}

int	ft_wait(int argc, int **fd)
{
	int	status;

	ft_close(argc - 3, fd);
	while (argc-- - 3)
		wait(&status);
	exit(0);
}

int	main(int argc, char *argv[], char **envp)
{
	int		**fd;
	pid_t	pid;
	int		i;

	if (argc != 5)
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
	ft_wait(argc, fd);
}
