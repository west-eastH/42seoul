/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:37:03 by youwin0802        #+#    #+#             */
/*   Updated: 2023/09/04 15:46:42 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_strings(char **strings)
{
	int	i;

	i = 0;
	while (strings && strings[i])
		free(strings[i++]);
	if (strings)
		free(strings);
}

char	*join_n_add(t_cmd_info *info, char *split)
{
	char	*temp;

	temp = ft_strjoin(info->str, split);
	*info->cmds = add_str(*info->cmds, temp);
	info->str = 0;
	return (NULL);
}
