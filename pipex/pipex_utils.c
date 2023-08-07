/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:28:11 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/07 16:40:43 by dongseo          ###   ########.fr       */
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
		ft_perror("malloc");
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
		ft_perror("malloc");
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
			file_close(fd[i][j]);
			j++;
		}
		i++;
	}
}

int	**make_pipe(int cnt, char *argv[])
{
	int	i;
	int	**result;

	if (access(argv[1], R_OK) != 0)
		ft_perror("file open");
	result = (int **)malloc(sizeof(int *) * (cnt));
	if (!result)
		ft_perror("malloc");
	i = 0;
	while (i < cnt)
	{
		result[i] = (int *)malloc(sizeof(int) * 2);
		if (!result[i])
			ft_perror("malloc");
		i++;
	}
	return (result);
}
