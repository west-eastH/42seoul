/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:02:49 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/28 15:23:32 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_print(int flag, t_info *info, t_cmd *cmd);
void	print_status(t_info *info, t_cmd *cmd);

void	leaks(void)
{
	system("leaks pipex");
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	t_cmd	cmd;
	int		idx;

	info.limiter = 0;
	if (!ft_strncmp(argv[1], "here_doc", 9))
		check_heredoc(argc, argv, envp, &info);
	else
		check_input(argc, argv, envp, &info);
	if (pipe(info.fds) == -1)
		error_print(0, &info, &cmd);
	idx = -1;
	while (++idx < info.cmd_nums)
		execute_cmds(&info, &cmd, idx);
	if (close(info.prev_fd) == -1 || close(info.fds[0]) == -1 \
	|| close(info.fds[1]) == -1)
		error_print(0, &info, &cmd);
	wait_n_exit(&info);
}

void	error_print(int flag, t_info *info, t_cmd *cmd)
{
	if (flag == INFILE_ERROR)
	{
		ft_printf("pipex: ");
		perror(info->infile);
	}
	else if (flag == COMMAND_ERROR)
		ft_printf("pipex: %s: command not found\n", *cmd->cmds);
	else
		perror("pipex");
	exit(EXIT_FAILURE);
}

// void	print_status(t_info *info, t_cmd *cmd)
// {
// 	int	idx;

// 	ft_printf("infile: [%s]\n", info->infile);
// 	ft_printf("outfile: [%s]\n", info->outfile);
// 	if (info->limiter)
// 		ft_printf("limiter: [%s]\n", info->limiter);
// 	ft_printf("\n");
// 	idx = -1;
// 	while (++idx < info->cmd_nums)
// 		ft_printf("%d cmd_argv: [%s]\n", idx, info->cmd_argv[idx]);
// 	ft_printf("\n");
// 	idx = -1;
// 	while (++idx < info->cmd_nums)
// 		ft_printf("%d path: [%s]\n", idx, info->path[idx]);
// 	ft_printf("\n");
// }
