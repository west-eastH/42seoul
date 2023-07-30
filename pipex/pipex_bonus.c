/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:25:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/30 20:59:18 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_perror(char *msg)
{
	perror(msg);
	exit(1);
}

int	ft_wait(int argc, int **fd, int is_here_doc, char *temp)
{
	int	status;

	if (is_here_doc)
	{
		if (unlink("temp.txt") < 0)
			ft_perror("unlink error");
		free(temp);
	}
	ft_close(argc - 3, fd);
	while (argc-- - 3)
		wait(&status);
	exit(0);
}

void	make_temp(char *argv[])
{
	size_t	limit_len;
	int		temp;
	char	*str;

	limit_len = ft_strlen(argv[2]);
	temp = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp < 0)
		ft_perror("file open error");
	str = get_next_line(0);
	if (str == NULL)
		ft_perror("input is null");
	while (!(ft_strncmp(str, argv[2], limit_len) == 0
			&& str[limit_len] == '\n'))
	{
		write(temp, str, ft_strlen(str));
		free(str);
		str = get_next_line(0);
	}
	free(str);
	close(temp);
}

void	ft_here_doc(int*argc, char *argv[], t_idx *idx)
{
	int	i;

	if (*argc < 5)
		perror("argc error");
	idx->is_here_doc = 0;
	if (ft_strncmp(argv[1], "here_doc", 9) != 0)
		return ;
	if (*argc < 6)
		ft_perror("argc error");
	make_temp(argv);
	i = 2;
	argv[1] = ft_strdup("temp.txt");
	if (!argv[1])
		ft_perror("malloc error");
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
				ft_perror("pipe error");
		pid = fork();
		if (pid < 0)
			ft_perror("fork error");
		else if (pid == 0 && idx.i == 0)
			first_child(fd, argv, envp);
		else if (pid == 0 && idx.i == argc - 4)
			last_child(fd, argv, envp, &idx);
		else if (pid == 0)
			middle_child(fd, argv, envp, idx.i);
		idx.i++;
	}
	ft_wait(argc, fd, idx.is_here_doc, argv[1]);
}
