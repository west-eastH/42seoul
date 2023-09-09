/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:43:09 by dongseo           #+#    #+#             */
/*   Updated: 2023/09/04 15:53:08 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **cmd, t_package *pack)
{
	int		result;
	char	*temp;

	temp = getcwd(0, 0);
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
		result = chdir(find_env("HOME", pack)->value);
	else if (!ft_strcmp(cmd[1], "-"))
	{
		if (!find_env("OLDPWD", pack))
		{
			printf("minishell😎: cd: OLDPWD not set\n");
			g_exit_status = 1;
			return (1);
		}
		result = chdir(find_env("OLDPWD", pack)->value);
		pwd();
	}
	else
		result = chdir(cmd[1]);
	check_result(result, pack, temp, cmd[1]);
	return (1);
}

void	check_result(int result, t_package *pack, char *temp, char *cmd)
{
	t_env	*pwd_dir;

	if (!result)
	{
		add_env_node(pack, "OLDPWD", temp);
		free(temp);
		pwd_dir = find_env("PWD", pack);
		free(pwd_dir->value);
		pwd_dir->value = getcwd(0, 0);
		g_exit_status = 0;
	}
	else
	{
		printf("minishell😎: cd: %s: No such file or directory\n", cmd);
		g_exit_status = 1;
	}
}

int	solo_builtin(t_cmd *cur, t_package *pack)
{
	int	std_fd[2];
	int	in_fd;
	int	out_fd;
	int	res;

	res = 0;
	builtin_fd_set(&in_fd, &out_fd, std_fd);
	check_redir(cur, std_fd, &in_fd, &out_fd);
	if (in_fd != 0)
		close(in_fd);
	if (out_fd != 1)
		close(out_fd);
	if (check_builtin(cur->cmd_args, pack))
		res = 1;
	if (cur->infile)
	{
		dup2(std_fd[0], 0);
		close(std_fd[0]);
	}
	if (cur->outfile)
	{
		dup2(std_fd[1], 1);
		close(std_fd[1]);
	}
	return (res);
}

void	builtin_fd_set(int *in_fd, int *out_fd, int *std_fd)
{
	*in_fd = 0;
	*out_fd = 1;
	std_fd[0] = 0;
	std_fd[1] = 1;
}

void	check_redir(t_cmd *cur, int *std_fd, int *in_fd, int *out_fd)
{
	if (cur->infile)
	{
		std_fd[0] = dup(0);
		*in_fd = open(cur->infile->filename[1], O_RDONLY);
		dup2(*in_fd, 0);
	}
	if (cur->outfile)
	{
		std_fd[1] = dup(1);
		if (cur->outfile->type == L_D_GREATER)
			*out_fd = open(cur->outfile->filename[1],
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			*out_fd = open(cur->outfile->filename[1],
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(*out_fd, 1);
	}
}
