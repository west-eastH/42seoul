/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:29:05 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/28 15:53:10 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	append_redir(t_cmd *new_cmd, t_token **temp)
{
	t_redir	*redir_temp;
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		exit(1);
	new->filename = 0;
	new->fd = -1;
	new->next = 0;
	new->type = (*temp)->prev->type;
	new->filename = expand_scanner(&(new->filename), (*temp)->data, 0);
	new->filename = expand_scanner(&(new->filename), (*temp)->data, 1);
	if (!(new_cmd->redirection))
		new_cmd->redirection = new;
	else
	{
		redir_temp = new_cmd->redirection;
		while (redir_temp && redir_temp->next)
			redir_temp = redir_temp->next;
		redir_temp->next = new;
	}
}

t_token	*build_simple_cmd(t_cmd **head, t_cmd **last, t_token *node)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit(1);
	new->redirection = 0;
	new->next = 0;
	new->cmd_args = 0;
	new->prev_fd = 0;
	new->infile = 0;
	new->outfile = 0;
	while (node && node->type != L_PIPE)
	{
		if (node->prev && node->prev->type > L_PIPE)
			append_redir(new, &node);
		else if (node->type == L_WORD)
			new->cmd_args = expand_scanner(&(new->cmd_args), node->data, 1);
		node = node->next;
	}
	if (*head)
		(*last)->next = new;
	else
		*head = new;
	(*last) = new;
	if (node && node->type == L_PIPE)
		node = node->next;
	return (node);
}

char	**expand_scanner(char ***cmds, char *data, int check)
{
	t_cmd_info	info;
	int			target_flag;

	target_flag = 0;
	init_info(&info, cmds);
	while (data[info.idx + info.len])
	{
		target_flag = is_target(data[info.idx + info.len], info.flag, check);
		if (target_flag)
			update_string(&info, data, target_flag, check);
		else
			info.len++;
		if (!data[info.idx + info.len])
			update_string(&info, data, -1, check);
	}
	if (info.str == 0 && !info.expand_flag)
		info.str = "";
	return (add_str(*cmds, info.str));
}

t_cmd	*parser(t_token	*head)
{
	t_cmd	*cmd_head;
	t_cmd	*cmd_last;
	t_token	*temp;

	temp = head;
	cmd_head = 0;
	cmd_last = 0;
	if (!head)
		return (0);
	if (check_syntax(head))
		return (0);
	while (temp)
		temp = build_simple_cmd(&cmd_head, &cmd_last, temp);
	print_cmd(cmd_head);
	return (cmd_head);
}
