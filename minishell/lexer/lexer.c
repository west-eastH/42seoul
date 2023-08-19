/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:22:38 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/17 10:52:58 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

enum e_types	check_stat(char c)
{
	if (c == '|')
		return (L_PIPE);
	else if (c == '<')
		return (L_LESSER);
	else if (c == '>')
		return (L_GREATER);
	else if (c == ' ' || (c >= 9 && c <= 13))
		return (L_SPACE);
	else
		return (L_WORD);
}

void	addback_new_tok(t_token **head, char *data, enum e_types stat)
{
	t_token	*new;
	t_token	*temp;

	new = malloc(sizeof(t_token));
	if (!new)
		exit(1);
	new->type = stat;
	new->data = data;
	new->next = 0;
	if (!(*head))
	{
		*head = new;
		(*head)->prev = 0;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}

void	clear_token_list(t_token **head)
{
	t_token		*temp;

	temp = *head;
	while (temp)
	{
		*head = (*head)->next;
		free(temp);
		temp = (*head);
	}
	*head = 0;
}

int	build_token(t_token **head, char *line, enum e_types stat)
{
	char		*token;
	int			len;
	int			flag;

	flag = 0;
	len = 0;
	while (!(1 < stat && 1 < len) && (line[len]
			&& (flag || stat == check_stat(line[len]))))
	{
		if (flag && line[len] == flag)
			flag = 0;
		else if (!flag && (line[len] == '\'' || line[len] == '"'))
			flag = line[len];
		len++;
	}
	len -= (1 < len && stat == L_PIPE);
	if (flag)
		clear_token_list(head);
	else
	{
		token = malloc(sizeof(char) * (len + 1));
		if (!token)
			exit(1);
		token[len] = '\0';
		ft_memcpy(token, line, len);
		addback_new_tok(head, token, stat);
	}
	return (len);
}

t_token	*lexer(char *readline, t_token **head)
{
	int	idx;

	idx = 0;
	*head = 0;
	if (!readline)
		return (*head);
	while (readline[idx])
	{
		if (check_stat(readline[idx]) == L_SPACE)
			idx++;
		else
			idx += build_token(head, readline + idx, check_stat(readline[idx]));
	}
	return (*head);
}
