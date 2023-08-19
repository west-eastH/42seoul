/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:47:51 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/17 14:41:12 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax(t_token *head)
{
	int		flag;
	t_token	prev;

	flag = 0;
	prev.type = L_ERROR;
	while (head && !flag)
	{
		if ((head->type == L_PIPE && prev.type != L_WORD)
			|| (head->type > L_PIPE && prev.type > L_PIPE))
			flag = printf("syntax error near unexpected token '%s'\n", head->data);
		else if (head->type == L_PIPE && !head->next)
			flag = printf("syntax error: unexpected end of file\n");
		else if (head->type > L_PIPE && !head->next)
			flag = printf("syntax error near unexpected token `newline'\n");
		prev.type = head->type;
		prev.data = head->data;
		head = head->next;
	}
	return (flag);
}

int		expand(char *word)
{
	int 	len;
	t_env	*temp;

	len = 0;
	temp = g_package.origin_head;
	while (word[len] && !ft_isdigit(word[0])
		&& (ft_isalnum(word[len]) || word[len] == '_'))
	{
		len++;
	}
	while (temp && ft_strcmp(temp->name, word))
		temp = temp->origin_next;
	if (temp)
		temp->value;
	else
		
}

void	expand_searcher(t_token *head)
{
	int		i;
	int		len;
	int		flag;
	char	*temp;
	char	*expaned;
	char	*new_token;

	flag = 0;
	while (head->data[i])
	{
		if (flag && head->data[i] == flag)
			flag = 0;
		else if (!flag && (head->data[i] == '\'' || head->data[i] == '"'))
			flag = head->data[i];
		else if (flag != '\'' && head->data[i] == '$')
		{
			new_token = ft_strjoin(new_token, ft_strndup(head->data + i, len));
			new_token = ft_strjoin(new_token, expand(head->data + i + 1));
			len = 0;
		}	
		i++;
		len++;
	}
}

void	parser(t_token *head)
{
	if (check_syntax(head))
		exit (1);
	expand_searcher(head);
	//redirection - word : struct save && open=≠
	//word - word : struct save
	
}