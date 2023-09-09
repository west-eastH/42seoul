/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:22:38 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/03 13:14:54 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_word(t_token **head, char *line, enum e_type stat)
{
	int		len;
	int		flag;

	flag = 0;
	len = 0;
	while (line[len] && (flag || stat == check_stat(line[len])))
	{
		if (flag && line[len] == flag)
			flag = 0;
		else if (!flag && (line[len] == '\'' || line[len] == '"'))
			flag = line[len];
		else if (flag != '\'' && line[len] == '\\')
		{
			if (line[len + 1] == 0)
				flag = '\\';
			else
				len++;
		}
		len++;
	}
	if (flag)
		clear_token(head);
	else
		add_new_tok(head, line, len, stat);
	return (len);
}

int	build_symbol(t_token **head, char *line, enum e_type stat)
{
	int	len;

	len = 0;
	if (stat == L_PIPE)
	{
		add_new_tok(head, line, 1, stat);
		return (1);
	}
	while (line[len] && stat == check_stat(line[len]))
	{
		if (stat == L_LESSER && len == 1)
		{
			stat = L_D_LESSER;
			break ;
		}
		if (stat == L_GREATER && len == 1)
		{
			stat = L_D_GREATER;
			break ;
		}
		len++;
	}
	if (stat != L_SPACE)
		add_new_tok(head, line, len + (stat >= L_D_LESSER), stat);
	return (len +(stat >= L_D_LESSER));
}

t_token	*lexer(char	*line)
{
	t_token		*head;
	enum e_type	type;
	int			idx;

	idx = 0;
	head = 0;
	while (line[idx])
	{
		type = check_stat(line[idx]);
		if (type > L_WORD)
			idx += build_symbol(&head, line + idx, type);
		else if (type == L_WORD)
			idx += build_word(&head, line + idx, type);
	}
	return (head);
}
