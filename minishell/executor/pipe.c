/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:12:41 by dongseo           #+#    #+#             */
/*   Updated: 2023/09/11 10:40:54 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_exec(t_cmd	*cur, t_package *pack)
{
	char	**envp;

	envp = make_envp(pack);
	if (is_route(cur->cmd_args[0]))
	{
		if (execve(cur->cmd_args[0], cur->cmd_args, envp) < 0)
		{
			if (is_dir(cur->cmd_args[0]))
				ft_perror(cur->cmd_args[0], 126);
			else
				ft_perror(cur->cmd_args[0], 1);
		}
	}
	ft_execve(cur->cmd_args, pack, envp);
}

void	ft_execve(char **cmd, t_package *pack, char **envp)
{
	char	**split;
	int		i;
	char	*result;
	char	*path;

	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, envp);
	path = set_path(pack);
	if (path == NULL)
	{
		if (execve(cmd[0], cmd, envp) < 0)
			ft_perror(cmd[0], 127);
	}
	split = ft_split(path, ':');
	i = 0;
	while (split[i])
	{
		result = ft_cmdjoin(split[i], cmd[0]);
		if (access(result, X_OK) == 0)
		{
			if (execve(result, cmd, envp) < 0)
				ft_perror("execve", 1);
		}
		free(result);
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
	ft_perror(cmd[0], 127);
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
		ft_perror("malloc", 1);
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
