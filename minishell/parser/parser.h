/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:38:48 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/17 13:40:17 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../minishell.h"

enum	e_redir
{
	INFILE = 0,
	HEREDOC,
	OUTFILE,
	APPEND
};

typedef struct s_redir
{
	char			*filename;
	int				fd;
	enum e_redir	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd;
	t_redir			*greater;
	t_redir			*lesser;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

void	parser(t_token *head);
void	check_syntax(t_token *head);
#endif