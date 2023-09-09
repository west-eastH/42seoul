/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:53:54 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/03 18:47:23 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_info(t_cmd_info *info, char ***cmds, int check)
{
	info->expand_flag = 0;
	info->cmds = cmds;
	info->flag = 0;
	info->idx = 0;
	info->len = 0;
	info->str = 0;
	info->check = check;
}

int	is_target(char c, int flag, int check)
{
	if ((c == '"' && flag != '\'') || (c == '\'' && flag != '"')
		|| (c == '$' && flag != '\'' && check) || (c == '\\' && !flag))
		return (c);
	else
		return (0);
}

void	update_str(t_cmd_info *info, char *data, int c_flag, t_package *pack)
{
	char	*dup_str;

	dup_str = ft_strndup(data + info->idx, info->len);
	info->str = ft_strjoin(info->str, dup_str);
	if (dup_str)
		free(dup_str);
	if (c_flag == -1)
		return ;
	info->idx += info->len + 1;
	info->len = 0;
	if (c_flag == '\\')
		return (do_escape(info, data));
	if (c_flag == '\'' || c_flag == '"')
	{
		if (info->flag == c_flag)
			info->flag = 0;
		else if (!info->flag)
			info->flag = c_flag;
	}
	else if (info->flag != '\'' && c_flag == '$' && info->check)
		info->str = expand(info, data, pack);
	if (!info->str)
		info->expand_flag = 1;
}

char	**add_str(char **str, char *add)
{
	char	**new;
	int		i;

	if (!add)
		return (str);
	i = 0;
	while (str && str[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		exit(1);
	i = 0;
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = add;
	i++;
	new[i] = 0;
	if (str)
		free(str);
	return (new);
}

void	do_escape(t_cmd_info *info, char *data)
{
	char	*dup_str;

	dup_str = ft_strndup(data + info->idx++, 1);
	info->str = ft_strjoin(info->str, dup_str);
	if (dup_str)
		free(dup_str);
	return ;
}
