/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:28:01 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/27 18:51:26 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	*ft_readline(void)
{
	t_token		*token;
	t_cmd		*simple_cmds;
	char		*str;

	simple_cmds = 0;
	token = 0;
	str = readline("minishell😎$ ");
	if (str)
	{
		// printf("\n[%s]\n", str);
		token = lexer(str);
		print_tok(token);
		simple_cmds = parser(token);
		add_history(str);
		clear_token(&token);
		executor(simple_cmds);
		//system("leaks --list -- minishell");
	}
	return (str);
}

void	tracer(char *str, char *number)
{
	int		trace_fd;

	trace_fd = open("traces.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	write(trace_fd, "[", 1);
	write(trace_fd, number, 1);
	(*number)++;
	write(trace_fd, "]\t", 2);
	write(trace_fd, str, ft_strlen(str));
	write(trace_fd, "\n", 1);
	close(trace_fd);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
	else if (sig == SIGUSR1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
	//	write(1, "\n", 1);
	//	rl_redisplay();
	}
}

int	main(int argc, char *argv[], char **envp)
{
	char	number;
	char	*str;

	if (argc > 1)
	{
		printf("minishell😎: too many arguments\n");
		exit(1);
	}
	rl_catch_signals = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGUSR1, handler);
	(void)argv;
	g_package.origin_head = 0;
	init_env(envp, &g_package);
	number = 'A' - 1;
	tracer("------------------------------\n", &number);
	while (1)
	{
		str = ft_readline();
		if (str)
		{
			tracer(str, &number);
			free(str);
		}
		else
			break ;
	}
	rl_clear_history();
	builtin_exit(NULL);
	return (0);
}
