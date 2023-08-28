/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:53:54 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/27 18:31:56 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_info(t_cmd_info *info, char ***cmds)
{
	info->expand_flag = 0;
	info->cmds = cmds;
	info->flag = 0;
	info->idx = 0;
	info->len = 0;
	info->str = 0;
}

int	is_target(char c, int flag, int check)
{
	if ((c == '"' && flag != '\'') || (c == '\'' && flag != '"')
		|| (c == '$' && flag != '\'' && check) || (c == '\\' && flag != '\''))
		return (c);
	else
		return (0);
}

int	check_envlen(char *str)
{
	int	len;

	if (*str == ' ' || (*str >= 9 && *str <= 13))
		return (0);
	len = 0;
	if (ft_isdigit(*str))
		return (-1);
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
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

void	update_string(t_cmd_info *info, char *data, int cur_flag, int check)
{
	char	*dup_str;

	dup_str = ft_strndup(data + info->idx, info->len);
	info->str = ft_strjoin(info->str, dup_str);
	if (dup_str)
		free(dup_str);
	if (cur_flag == -1)
		return ;
	info->idx += info->len + 1;
	info->len = 0;
	if (cur_flag == '\\')
	{
		dup_str = ft_strndup(data + info->idx++, 1);
		info->str = ft_strjoin(info->str, dup_str);
		if (dup_str)
			free(dup_str);
		return ;
	}
	if (cur_flag == '\'' || cur_flag == '"')
	{
		if (info->flag == cur_flag)
			info->flag = 0;
		else if (!info->flag)
			info->flag = cur_flag;
	}
	else if (info->flag != '\'' && cur_flag == '$' && check)
		info->str = expand(info, data);
	if (!info->str)
		info->expand_flag = 1;
}
