/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:25:31 by dongseo           #+#    #+#             */
/*   Updated: 2023/09/06 13:51:30 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char **cmd, t_package *pack)
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp(*cmd, "export") == 0)
		return (export(cmd, pack));
	else if (ft_strcmp(*cmd, "env") == 0)
		return (print_env(pack->origin_head));
	else if (ft_strcmp(*cmd, "unset") == 0)
		return (unset(cmd, pack));
	else if (ft_strcmp(*cmd, "pwd") == 0)
		return (pwd());
	else if (ft_strcmp(*cmd, "cd") == 0)
		return (cd(cmd, pack));
	else if (ft_strcmp(*cmd, "echo") == 0)
		return (echo(cmd));
	else if (ft_strcmp(*cmd, "exit") == 0)
		return (builtin_exit(cmd));
	else
		return (0);
}

int	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	g_exit_status = 0;
	return (1);
}

int	echo(char **cmd)
{
	int	flag;
	int	i;

	flag = 0;
	if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
		flag = 1;
	i = 1;
	while (cmd[i + flag] && cmd[i + flag + 1])
		printf("%s ", cmd[i++ + flag]);
	if (cmd[i + flag])
		printf("%s", cmd[i + flag]);
	if (flag == 0)
		printf("\n");
	g_exit_status = 0;
	return (1);
}

int	builtin_exit(char **cmd)
{
	g_exit_status = 0;
	printf("goodbye\n");
	if (cmd && cmd[1])
	{
		if (check_sign(cmd[1]))
		{
			printf("minishell😎: exit: %s: numeric argument required\n", cmd[1]);
			g_exit_status = 255;
			exit(g_exit_status);
		}
		if (cmd[2])
		{
			printf("minishell😎: exit: too many arguments\n");
			g_exit_status = 1;
			return (1);
		}
		else
			g_exit_status = ft_atoi(cmd[1]) % 256;
	}
	display_image(0);
	exit(g_exit_status);
}

int	check_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (((i == 0 && str[i] == '-') || (i == 0 && str[i] == '+'))
				&& str[i + 1] >= '0' && str[i + 1] <= '9')
			{
				i++;
				continue ;
			}
			return (1);
		}
		i++;
	}
	return (0);
}
