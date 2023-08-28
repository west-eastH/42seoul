/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:30:28 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/21 15:30:31 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

enum	e_type
{
	L_ERROR = -1,
	L_WORD,
	L_SPACE,
	L_PIPE,
	L_LESSER,
	L_GREATER,
	L_D_LESSER,
	L_D_GREATER
};

typedef struct s_token
{
	enum e_type		type;
	char			*data;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

t_token		*lexer(char	*line);
void		clear_token(t_token **head);
enum e_type	check_stat(char c);
void		add_new_tok(t_token **head, char *line, int len, enum e_type stat);

#endif
