/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:03:55 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/05 18:29:04 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		error_print(0, 0, 0);
	out[size] = '\0';
	while (n)
	{
		out[--size] = (n % 10) + '0';
		n /= 10;
	}
	return (out);
}

void	do_heredoc(t_info *info)
{
	int		infile_fd;
	int		limiter_len;
	char	*user_input;

	limiter_len = ft_strlen(info->limiter);
	info->limiter[limiter_len] = '\n';
	infile_fd = open(info->infile, O_WRONLY | O_CREAT, 0644);
	if (infile_fd == -1)
		error_print(INFILE_ERROR, 0, 0);
	user_input = get_next_line(0);
	if (!user_input)
		return ;
	while (ft_strncmp(user_input, info->limiter, limiter_len + 1))
	{
		write(infile_fd, user_input, ft_strlen(user_input));
		free(user_input);
		user_input = get_next_line(0);
		if (!user_input)
			break ;
	}
	free(user_input);
	if (close(infile_fd) == -1)
		error_print(0, 0, 0);
}

void	check_heredoc(int argc, char **argv, char **envp, t_info *info)
{
	char	*tmp_file;
	char	*itoa_out;
	int		num;

	num = -1;
	tmp_file = "heredoc_tmp";
	info->infile = tmp_file;
	while (!access(info->infile, F_OK))
	{
		if (ft_strlen(info->infile) != 11)
		{
			free(info->infile);
			if (num > 0)
				free(itoa_out);
		}
		itoa_out = itoa(++num);
		info->infile = ft_strjoin(tmp_file, itoa_out);
	}
	info->limiter = argv[2];
	info->outfile = argv[argc - 1];
	info->cmd_nums = argc - 4;
	argv += 3;
	info->cmd_argv = argv;
	check_input(argc, argv, envp, info);
	do_heredoc(info);
}
