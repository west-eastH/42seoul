/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:29:49 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/06 14:20:41 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtins.h"
# include "pipe.h"
# include "env_utils.h"
# include "../libft/libft.h"

void		display_image(int flag);
void		print_export(t_env *head);

int			g_exit_status;
void		error_print(char *msg);
void		handler(int sig);
#endif
