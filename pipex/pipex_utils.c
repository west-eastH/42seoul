/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:28:11 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/31 10:41:58 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*set_path(char **envp)
{
	char	*result;
	int		i;

	i = 0;
	while (envp[i++])
	{
		if (ft_strncmp(envp[i - 1], "PATH=", 5) == 0)
			break ;
	}
	result = ft_strdup(envp[i - 1]);
	if (!result)
		ft_perror("malloc error");
	return (result);
}

char	*ft_cmdjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	temp = (char *)malloc(s1_len + s2_len + 2);
	if (!temp)
		ft_perror("malloc error");
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '/';
	i++;
	j = 0;
	while (s2[j++])
		temp[i + j - 1] = s2[j - 1];
	temp[i + j - 1] = 0;
	return (temp);
}

void	ft_execve(char **cmd, char **envp)
{
	char	**split;
	int		i;
	char	*result;
	char	*path;

	path = set_path(envp);
	split = ft_split(path + 5, ':');
	i = 0;
	while (split[i])
	{
		result = ft_cmdjoin(split[i], cmd[0]);
		if (access(result, X_OK) == 0)
		{
			if (execve(result, cmd, envp) < 0)
				ft_perror("execve error");
		}
		free(result);
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
	ft_perror("command error");
}

void	ft_close(int cnt, int *fd[])
{
	int	i;
	int	j;

	i = 0;
	while (i < cnt - 1)
	{
		j = 0;
		while (j < 2)
		{
			close(fd[i][j]);
			j++;
		}
		i++;
	}
}

int	**make_pipe(int cnt)
{
	int	i;
	int	**result;

	result = (int **)malloc(sizeof(int *) * (cnt));
	if (!result)
		ft_perror("malloc error");
	i = 0;
	while (i < cnt)
	{
		result[i] = (int *)malloc(sizeof(int) * 2);
		if (!result[i])
			ft_perror("malloc error");
		i++;
	}
	return (result);
}
