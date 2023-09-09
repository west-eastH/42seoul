/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:29:55 by dongseo           #+#    #+#             */
/*   Updated: 2023/09/07 13:15:13 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(char **cmd, t_package *pack)
{
	if (cmd[1] == 0)
		print_export(pack->sorted_head);
	else
		add_export(cmd, pack);
	g_exit_status = 0;
	return (1);
}

void	print_export(t_env *head)
{
	char	*value;

	while (head)
	{
		value = head->value;
		printf("declare -x %s", head->name);
		if (value)
			printf("=\"%s\"", value);
		printf("\n");
		head = head->sorted_next;
	}
}

int	check_name(char *name)
{
	int	len;
	int	str_len;

	len = 0;
	str_len = ft_strlen(name);
	if (ft_isdigit(*name))
		return (1);
	while (len < str_len)
	{
		if (!(ft_isalnum(name[len]) || name[len] == '_'))
			return (1);
		len++;
	}
	return (0);
}

int	check_export(t_package *pack, char *cmd, char *addr)
{
	if (!addr)
	{
		if (check_name(cmd))
		{
			printf("minishell😎: export: '%s': not a valid identifier\n", cmd);
			g_exit_status = 1;
			return (1);
		}
		add_env_node(pack, cmd, 0);
	}
	else
	{
		*addr = 0;
		if (check_name(cmd))
		{
			printf("minishell😎: export: '%s': not a valid identifier\n", cmd);
			g_exit_status = 1;
			*addr = '=';
			return (1);
		}
		add_env_node(pack, cmd, addr + 1);
		*addr = '=';
	}
	return (0);
}

void	add_export(char **cmd, t_package *pack)
{
	char	*addr;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		addr = ft_strchr(cmd[i], '=');
		if (addr == cmd[i])
		{
			printf("minishell😎: export: '%s': not a valid identifier\n", addr);
			g_exit_status = 1;
			continue ;
		}
		if (check_export(pack, cmd[i], addr))
			continue ;
	}
}
