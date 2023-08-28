/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:29:49 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/22 13:42:42 by dongseo          ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtins.h"
# include "env_utils.h"
# include "../libft/libft.h"

// testprint functions
int			print_env(t_env *head);
void		print_export(t_env *head);
void		print_tok(t_token *head);
void		print_cmd(t_cmd *head);
#endif
