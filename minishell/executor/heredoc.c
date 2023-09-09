/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:39:31 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/05 17:41:23 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig);

int	do_heredoc(t_redir *temp, char *f_name, int len, t_package *pack)
{
	int		infile_fd;
	int		temp_e_stat;
	int		fd;

	infile_fd = open(f_name, O_WRONLY | O_CREAT, 0644);
	if (infile_fd == -1)
		exit(1);
	fd = dup(0);
	temp_e_stat = g_exit_status;
	g_exit_status = 0;
	write_heredoc(temp, pack, infile_fd, len);
	if (g_exit_status)
		dup2(fd, 0);
	signal(SIGINT, handler);
	free(temp->filename[1]);
	temp->filename[1] = f_name;
	if (close(infile_fd) == -1 || close(fd) == -1)
		exit(1);
	return (detact_exitcode(temp_e_stat));
}

void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_exit_status = 1;
		close(STDIN_FILENO);
	}
}

int	here_doc_open(t_redir *temp, t_package *pack)
{
	char	*tmp_file;
	char	*filename;
	char	*itoa_out;
	int		num;

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handler_heredoc);
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
	num = ft_strlen(temp->filename[0]);
	temp->filename[0][num] = '\n';
	return (do_heredoc(temp, filename, num, pack));
}
