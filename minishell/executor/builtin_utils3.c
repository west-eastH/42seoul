/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:15:39 by dongseo           #+#    #+#             */
/*   Updated: 2023/09/07 13:15:48 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(t_env *head)
{
	while (head)
	{
		if (head->value)
			printf("%s=%s\n", head->name, head->value);
		head = head->origin_next;
	}
	return (1);
}

int	unset(char **cmd, t_package *pack)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (check_envlen(cmd[i]) != (int)ft_strlen(cmd[i]))
		{
			printf("minishell😎: unset: '%s': not a valid identifier\n", cmd[i]);
			g_exit_status = 1;
		}
		else
			delete_env(cmd[i], pack);
		i++;
	}
	g_exit_status = 0;
	return (1);
}
