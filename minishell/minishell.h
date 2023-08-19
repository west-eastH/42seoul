/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:29:49 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/17 14:10:29 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include "./lexer/lexer.h"
# include "./parser/parser.h"


typedef struct s_env
{
	char 			*name;
	char 			*value;
	struct s_env	*origin_next;
	struct s_env	*sorted_next;
}	t_env;

typedef struct s_package
{
	int		exit_status;
	t_env	*origin_head;
	t_env	*origin_last;
	t_env	*sorted_head;
}	t_package;

t_package	g_package;

#endif
