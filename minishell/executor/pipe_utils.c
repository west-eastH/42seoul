/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:25:53 by dongseo           #+#    #+#             */
/*   Updated: 2023/09/06 13:11:37 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_route(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	is_dir(char *str)
{
	struct stat	path_stat;

	if (stat(str, &path_stat) != 0)
		ft_perror(str, 128);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	else
		return (0);
}

char	*set_path(t_package *pack)
{
	char	*result;
	t_env	*env;

	env = pack->origin_head;
	while (env && (ft_strncmp(env->name, "PATH", 5)))
		env = env->origin_next;
	result = ft_strdup(env->value);
	if (!result)
		ft_perror("malloc", 1);
	return (result);
}

char	**make_envp(t_package *pack)
{
	char	*temp_str;
	t_env	*cur;
	char	*equal_str;
	char	**result;

	result = 0;
	temp_str = 0;
	cur = pack->origin_head;
	while (cur)
	{
		temp_str = ft_strjoin(temp_str, cur->name);
		equal_str = ft_strdup("=");
		temp_str = ft_strjoin(temp_str, equal_str);
		free(equal_str);
		temp_str = ft_strjoin(temp_str, cur->value);
		result = add_str(result, temp_str);
		temp_str = 0;
		cur = cur->origin_next;
	}
	return (result);
}
