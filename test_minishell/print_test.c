/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:28:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/24 14:10:05 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*convert_type(int type)
{
	if (type == -1)
		return ("L_ERROR");
	else if (type == 0)
		return ("L_WORD");
	else if (type == 1)
		return ("L_SPACE");
	else if (type == 2)
		return ("L_PIPE");
	else if (type == 3)
		return ("L_LESSER");
	else if (type == 4)
		return ("L_GREATER");
	else if (type == 5)
		return ("L_D_LESSER");
	else
		return ("L_D_GREATER");
}

void	print_tok(t_token	*head)
{
	t_token	*temp;
	int		idx;

	temp = head;
	idx = 0;
	if (!temp)
		printf("NO NODE\n");
	while (temp)
	{
		printf("%d token: [%s][%s]\n",
			idx++, convert_type(temp->type), temp->data);
		temp = temp->next;
	}
}

int	print_env(t_env *head)
{
	while (head)
	{
		if (head->value)
			printf("%s=%s\n", head->name, head->value);
		head = head->origin_next;
	}
	return 1;
}

void	print_export(t_env *head)
{
	char	*value;

	while (head)
	{
		value = head->value;
		if (!value)
			value = "";
		printf("declare -x %s=%s\n", head->name ,value);
		head = head->sorted_next;
	}
}

void	print_cmd(t_cmd *head)
{
	t_redir	*redirection;
	int		i;
	int		node;

	node = 0;
	while (head)
	{
		printf("--------------- simple cmd node[%d] ---------------\n", node++);
		i = 0;
		while (head->cmd_args && head->cmd_args[i])
		{
			printf("arg[%d] = [%s]\n", i, head->cmd_args[i]);
			i++;
		}
		redirection = head->redirection;
		while (redirection)
		{
			i = 0;
			while (redirection->filename[i])
			{
				printf("redirection: [%s][%s]\n",
					convert_type(redirection->type), redirection->filename[i]);
				i++;
			}
			redirection = redirection->next;
		}
		//printf("next address %p\n", head->next);
		head = head->next;
		printf("\n");
	}
}