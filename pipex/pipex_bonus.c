/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:25:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/12 10:39:40 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_perror(char *msg)
{
	perror(msg);
	exit(1);
}

int	ft_wait(int argc, char *argv[], int is_here_doc, int last_pid)
{
	int		status;
	int		exit_num;

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
	if (is_here_doc)
	{
		if (unlink(argv[1]) < 0)
			ft_perror("unlink");
		free(argv[1]);
	}
	exit(exit_num);
}

void	make_temp(char *argv[])
{
	size_t	limit_len;
	int		fd;
	char	*str;

	limit_len = ft_strlen(argv[2]);
	argv[1] = ft_strdup("temp");
	if (!argv[1])
		ft_perror("malloc");
	fd = temp_open(argv);
	str = get_next_line(0);
	while (str && !(ft_strncmp(str, argv[2], limit_len) == 0
			&& str[limit_len] == '\n'))
	{
		write(fd, str, ft_strlen(str));
		free(str);
		str = get_next_line(0);
	}
	free(str);
	file_close(fd);
}

void	ft_here_doc(int*argc, char *argv[], t_idx *idx)
{
	int	i;

	if (*argc < 5)
		ft_perror("argc");
	idx->is_here_doc = 0;
	if (ft_strncmp(argv[1], "here_doc", 9) != 0)
		return ;
	if (*argc < 6)
		ft_perror("argc");
	make_temp(argv);
	i = 2;
	while (i < *argc)
	{
		argv[i] = argv[i + 1];
		i++;
	}
	*argc = *argc - 1;
	idx->is_here_doc = 1;
}

int	main(int argc, char *argv[], char **envp)
{
	int		**fd;
	pid_t	pid;
	t_idx	idx;

	ft_here_doc(&argc, argv, &idx);
	fd = make_pipe(argc - 4);
	idx.i = 0;
	while (idx.i < argc - 3)
	{
		if (idx.i < argc - 4)
			if (pipe(fd[idx.i]) < 0)
				ft_perror("pipe");
		pid = fork();
		if (pid < 0)
			ft_perror("fork");
		else if (pid == 0 && idx.i == 0)
			first_child(fd, argv, envp);
		else if (pid == 0 && idx.i == argc - 4)
			last_child(fd, argv, envp, &idx);
		else if (pid == 0)
			middle_child(fd, argv, envp, idx.i);
		idx.i++;
	}
	ft_close(argc - 3, fd);
	ft_wait(argc, argv, idx.is_here_doc, pid);
}
