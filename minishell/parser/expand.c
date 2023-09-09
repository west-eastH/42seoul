/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:41:48 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/06 14:19:46 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_exit_stat(t_cmd_info *info)
{
	char	*itoa;
	char	*out;

	itoa = ft_itoa(g_exit_status);
	out = ft_strjoin(info->str, itoa);
	free(itoa);
	return (out);
}

char	*expand(t_cmd_info *info, char *data, t_package *pack)
{
	t_env	*env;
	char	*out;
	int		l;

	out = 0;
	env = pack->origin_head;
	l = check_envlen(data + info->idx);
	if (*(data + info->idx) == '?' || l < 0)
	{
		info->idx++;
		if (*(data + info->idx - 1) == '?')
			return (join_exit_stat(info));
		return (info->str);
	}
	else if (!l)
		return (ft_strjoin(info->str, "$"));
	while (env && (ft_strncmp(env->name, data + info->idx, l) || env->name[l]))
		env = env->origin_next;
	info->idx += l;
	if (!env)
		return (info->str);
	else
		return (split_join(info, env));
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
