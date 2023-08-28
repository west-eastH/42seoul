/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:03:01 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/05 18:36:10 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parse_argv(int argc, char **argv, t_info *info)
{
	info->outfile = argv[argc - 1];
	info->infile = *++argv;
	if (access(info->infile, F_OK | R_OK))
		error_print(INFILE_ERROR, info, 0);
	info->cmd_nums = argc - 3;
	info->cmd_argv = ++argv;
}

void	check_input(int argc, char **argv, char **envp, t_info *info)
{
	char	*temp;
	int		idx;
	int		len;

	if (!info->limiter)
		parse_argv(argc, argv, info);
	while (ft_strncmp(*envp++, "PATH=", 5))
		;
	info->path = ft_split((*--envp) + 5, ':');
	if (!info->path || !*info->path)
		error_print(0, 0, 0);
	idx = -1;
	while (info->path[++idx])
	{
		len = ft_strlen(info->path[idx]);
		if (info->path[idx][len - 1] != '/')
		{
			temp = ft_strjoin(info->path[idx], "/");
			if (!temp)
				error_print(0, 0, 0);
			free(info->path[idx]);
			info->path[idx] = temp;
		}
	}
}

void	parse_cmd(int idx, t_info *info, t_cmd *cmd)
{
	char	**cmd_tmp;
	char	*check;
	int		i;

	cmd_tmp = ft_split(info->cmd_argv[idx], ' ');
	if (!cmd_tmp || !*cmd_tmp)
		error_print(0, 0, 0);
	i = -1;
	while (info->path[++i])
	{
		check = ft_strjoin(info->path[i], *cmd_tmp);
		if (!check)
			error_print(0, 0, 0);
		if (!access(check, F_OK | X_OK))
		{
			cmd->cmd_path = check;
			cmd->cmds = cmd_tmp;
			return ;
		}
		free(check);
	}
	cmd->cmd_path = *cmd_tmp;
	cmd->cmds = cmd_tmp;
	error_print(COMMAND_ERROR, 0, cmd);
}
