/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:28:01 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/11 10:38:47 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(t_package *pack)
{
	t_token		*token;
	t_cmd		*simple_cmds;
	char		*str;

	simple_cmds = 0;
	token = 0;
	str = readline("minishell😎$ ");
	if (str)
	{
		token = lexer(str);
		simple_cmds = parser(token, pack);
		add_history(str);
		clear_token(&token);
		if (simple_cmds)
			executor(simple_cmds, pack, 0);
		signal(SIGINT, handler);
	}
	return (str);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	error_print(char *msg)
{
	if (msg)
		printf("%s", msg);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_package	package;

	(void)argv;
	g_exit_status = 0;
	if (argc > 1)
		error_print("minishell😎: too many arguments\n");
	display_image(1);
	rl_catch_signals = 0;
	signal(SIGTERM, handler);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	package.origin_head = 0;
	package.envp = 0;
	init_env(envp, &package);
	str = ft_readline(&package);
	while (str)
	{
		free(str);
		str = ft_readline(&package);
	}
	rl_clear_history();
	builtin_exit(NULL);
	return (0);
}

void	display_image(int flag)
{
	char	*str;
	char	**split;
	pid_t	pid;

	if (flag)
		str = "/bin/cat ./imgs/open_img";
	else
		str = "/bin/cat ./imgs/exit_img";
	pid = fork();
	if (pid == 0)
	{
		split = ft_split(str, ' ');
		if (execve(split[0], split, 0) == -1)
			exit (1);
	}
	else
		wait(0);
}
