/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:51:31 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/21 20:03:32 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_dup2(int fd, int fd2)
{
	int	result;

	result = dup2(fd, fd2);
	if (result < 0)
		ft_perror("dup2");
}

void	file_close(int fd)
{
	int	result;

	result = close(fd);
	if (result < 0)
		ft_perror("close");
}

int	file_open(char *file, int is_here_doc)
{
	int	out;

	if (is_here_doc == 1)
		out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (out);
}

void	command_error(char **cmd)
{
	char	*temp;
	int		i;

	if (cmd[0] == NULL || !cmd)
	{
		write(2, " : command not found\n", 21);
		exit(127);
	}
	i = 0;
	temp = 0;
	while (cmd[i])
	{
		temp = ft_strjoin(temp, cmd[i]);
		i++;
	}
	write(2, temp, ft_strlen(temp));
	write(2, ": command not found\n", 21);
	exit(127);
}
