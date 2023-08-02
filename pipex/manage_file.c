/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:51:50 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/02 20:13:27 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
