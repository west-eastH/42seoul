/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:14:23 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/21 17:31:40 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_envlen(char *str)
{
	int	len;

	if (*str == ' ' || (*str >= 9 && *str <= 13))
		return (0);
	len = 0;
	if (ft_isdigit(*str))
		return (-1);
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

char	**add_str(char **str, char *add)
{
	char	**new;
	int		i;

	if (!add)
		return (str);
	i = 0;
	while (str && str[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		exit(1);
	i = 0;
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = ft_strdup(add);
	i++;
	new[i] = 0;
	if (str)
		free(str);
	return (new);
}

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
			flag = printf("syntax error near unexpected token '%s'\n",
					head->data);
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
