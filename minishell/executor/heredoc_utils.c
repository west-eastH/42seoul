/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:21:24 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/10 12:22:07 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc(t_redir *temp, t_package *pack, int fd, int len)
{
	char	*user_input;

	user_input = 0;
	while (1)
	{
		if (user_input)
		{
			heredoc_expander(fd, user_input, pack);
			free(user_input);
		}
		write(1, "here🐶> ", 10);
		user_input = get_next_line(0);
		if (!user_input || !ft_strncmp(user_input, temp->filename[0], len + 1))
		{
			if (user_input)
				free(user_input);
			return ;
		}
	}
}

int	detact_exitcode(int temp)
{
	if (g_exit_status)
		return (1);
	else
	{
		g_exit_status = temp;
		return (0);
	}
}

void	heredoc_expander(int infile, char *line, t_package *pack)
{
	int		i;
	int		j;
	int		expand_len;
	char	*env_name;
	t_env	*env;

	i = 0;
	while (line[i])
	{
		expand_len = 0;
		if (line[i] == '$')
		{
			expand_len = check_envlen(line + i + 1);
			env_name = ft_strndup(line + i + 1, expand_len);
			env = find_env(env_name, pack);
			free(env_name);
			j = 0;
			while (env && env->value && env->value[j])
				write(infile, env->value + j++, 1);
		}
		else
			write(infile, line + i, 1);
		i += expand_len + 1;
	}
}

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
