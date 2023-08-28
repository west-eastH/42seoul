/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:53:23 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/27 15:53:46 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_type	check_stat(char c)
{
	if (c == '|')
		return (L_PIPE);
	else if (c == '<')
		return (L_LESSER);
	else if (c == '>')
		return (L_GREATER);
	else if (c == ' ' || (c >= 0 && c <= 13))
		return (L_SPACE);
	else
		return (L_WORD);
}

void	clear_token(t_token **head)
{
	t_token	*temp;

	temp = *head;
	while (temp)
	{
		free((*head)->data);
		*head = (*head)->next;
		free(temp);
		temp = (*head);
	}
	*head = 0;
}

void	add_new_tok(t_token **head, char *line, int len, enum e_type stat)
{
	char	*token;
	t_token	*new;
	t_token	*temp;

	token = malloc(sizeof(char) * (len + 1));
	new = malloc(sizeof(t_token));
	if (!token || !new)
		exit(1);
	token[len] = '\0';
	ft_memcpy(token, line, len);
	new->type = stat;
	new->data = token;
	new->next = 0;
	new->prev = 0;
	if (!(*head))
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}
