/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:12:41 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/28 16:18:55 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*itoa(int n)
{
	int		size;
	int		temp;
	char	*out;

	if (n == 0)
		return ("0");
	size = 0;
	temp = n;
	while (temp)
	{
		temp /= 10;
		size++;
	}
	out = malloc(sizeof(char) * (size + 1));
	if (!out)
		exit(1);
	out[size] = '\0';
	while (n)
	{
		out[--size] = (n % 10) + '0';
		n /= 10;
	}
	return (out);
}

void	do_heredoc(t_redir *temp, char *filename)
{
	int		infile_fd;
	int		limiter_len;
	char	*user_input;

	limiter_len = ft_strlen(temp->filename[0]);
	temp->filename[0][limiter_len] = '\n';
	infile_fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (infile_fd == -1)
		exit(1);
	write(1, "> ", 2);
	user_input = get_next_line(0);
	if (!user_input)
		return ;
	while (ft_strncmp(user_input, temp->filename[0], limiter_len + 1))
	{
		write(infile_fd, user_input, ft_strlen(user_input));
		free(user_input);
		write(1, "> ", 2);
		user_input = get_next_line(0);
		if (!user_input)
			break ;
	}
	free(user_input);
	free(temp->filename[1]);
	temp->filename[1] = filename;
	if (close(infile_fd) == -1)
		exit(1);
}

void	here_doc_open(t_redir *temp)
{
	char	*tmp_file;
	char	*filename;
	char	*itoa_out;
	int		num;

	num = -1;
	tmp_file = "heredoc_tmp";
	filename = ft_strdup(tmp_file);
	while (!access(filename, F_OK))
	{
		free(filename);
		itoa_out = itoa(++num);
		filename = ft_strjoin(ft_strdup(tmp_file), itoa_out);
		if (num > 0)
			free(itoa_out);
	}
	do_heredoc(temp, filename);
}
