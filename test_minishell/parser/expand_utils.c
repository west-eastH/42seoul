/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:37:03 by youwin0802        #+#    #+#             */
/*   Updated: 2023/08/27 19:00:12 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(t_cmd_info *info, char *data)
{
	t_env	*env;
	char	*out;
	int		l;

	out = 0;
	env = g_package.origin_head;
	l = check_envlen(data + info->idx);
	if (!l)
	{
		out = ft_strjoin(info->str, "$");
		return (out);
	}
	else if (l < 0)
	{
		info->idx++;
		return (info->str);
	}
	while (env && (ft_strncmp(env->name, data + info->idx, l) || env->name[l]))
		env = env->origin_next;
	info->idx += l;
	if (!env)
		return (info->str);
	else
		return (split_join(info, env));
}

void	free_strings(char **strings)
{
	int	i;

	i = 0;
	while (strings && strings[i])
		free(strings[i++]);
	if (strings)
		free(strings);
}

char	*split_join(t_cmd_info *info, t_env *env)
{
	char	**split;
	char	*out;

	if (info->flag == '"' || !env->value)
	{
		out = ft_strjoin(info->str, env->value);
		return (out);
	}
	split = ft_split(env->value, ' ');
	if (!split)
		exit(1);
	if (ft_isspace(env->value[0]))
	{
		*info->cmds = add_str(*info->cmds, info->str);
		info->str = NULL;
	}
	out = check_split(info, env, split);
	free_strings(split);
	return (out);
}

char	*check_split(t_cmd_info *info, t_env *env, char **split)
{
	char	*temp;
	int		jdx;

	jdx = -1;
	if (split[1] == 0)
	{
		if (ft_isspace(env->value[ft_strlen(env->value) - 1]))
			return (join_n_add(info, split[0]));
		else
		{
			temp = ft_strjoin(info->str, split[0]);
			return (temp);
		}
	}
	while (split[++jdx + 1])
		info->str = join_n_add(info, split[jdx]);
	if (ft_isspace(env->value[ft_strlen(env->value) - 1]))
		return (join_n_add(info, split[jdx]));
	else
		return (ft_strdup(split[jdx]));
}

char	*join_n_add(t_cmd_info *info, char *split)
{
	char	*temp;

	temp = ft_strjoin(info->str, split);
	*info->cmds = add_str(*info->cmds, temp);
	info->str = 0;
	return (NULL);
}
