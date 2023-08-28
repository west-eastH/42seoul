/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youwin0802 <youwin0802@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:47:51 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/26 21:39:27 by youwin0802       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*p_expand(char ***cmds, char *word, int *i, int flag, char **new_token)
{
	int		len;
	t_env	*temp;
	char	**split;
	int		j;

	len = 0;
	temp = g_package.origin_head;
	len = check_envlen(word);
	if (len == 0)
		return (ft_strjoin(*new_token, "$"));
	else if (len < 0)
	{
		(*i)++;
		return (*new_token);
	}
	while (temp && (ft_strncmp(temp->name, word, len) || temp->name[len]))
	{
		temp = temp->origin_next;
	}
	if (temp && flag) // double quote exist
	{
		*i = *i + len;
		return (ft_strjoin(*new_token, temp->value));
	}
	else if (temp && !flag) // double quote doesn't exist
	{
		split = ft_split(temp->value, ' ');
		j = 0;
		if (ft_isspace(temp->value[0]))
		{
			*cmds = add_str(*cmds, *new_token);
			*new_token = NULL;
		}
		if (split[j + 1] == 0)
		{
			*i += len;
			if (ft_isspace(temp->value[ft_strlen(temp->value) - 1]))
			{
				*cmds = add_str(*cmds, ft_strjoin(*new_token, split[j]));
				return (0);
			}
			else
				return (ft_strjoin(*new_token, split[j]));
		}
		while (split[j + 1])
		{
			*cmds = add_str(*cmds, ft_strjoin(*new_token, split[j]));
			free(*new_token);
			*new_token = 0;
			j++;
		}
		*i += len;
		if (ft_isspace(temp->value[ft_strlen(temp->value) - 1]))
		{
			*cmds = add_str(*cmds, ft_strjoin(*new_token, split[j]));
			return (0);
		}
		else
			return (split[j]);
	}
	*i += len;
	return (*new_token);
}

char	**expand_searcher(char ***cmds, char *data, int check)
{
	int		i;
	int		len;
	int		flag;
	int		check_add;
	char	*new_token;

	flag = 0;
	len = 0;
	i = 0;
	new_token = 0;
	while (data[i + len])
	{
		if (flag && data[i + len] == flag)
		{
			flag = 0;
			new_token = ft_strjoin(new_token, ft_strndup(data + i, len));
			i += len + 1;
			len = 0;
		}
		else if (!flag && (data[i + len] == '\'' || data[i + len] == '"'))
		{
			flag = data[i + len];
			new_token = ft_strjoin(new_token, ft_strndup(data + i, len));
			i += len + 1;
			len = 0;
		}
		else if (flag != '\'' && data[i + len] == '$' && check)
		{
			new_token = ft_strjoin(new_token, ft_strndup(data + i, len));
			i += len + 1;
			len = 0;
			new_token = p_expand(cmds, data + i, &i, flag, &new_token);
			if (!new_token)
				check_add = 1;
		}
		else
			len++;
		if (!data[i + len])
		{
			new_token = ft_strjoin(new_token, ft_strndup(data + i, len));
		}
	}
	if (new_token == 0 && !check_add)
		new_token = "";
	return (add_str(*cmds, new_token));
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

t_token	*build_simple_cmd(t_cmd **head, t_cmd **last, t_token *tok_head)
{
	t_cmd	*new;
	t_token	*temp;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit(1);
	new->redirection = 0;
	new->next = 0;
	new->cmd_args = 0;
	temp = tok_head;
	while (temp && temp->type != L_PIPE)
	{
		if (temp->prev && temp->prev->type > L_PIPE)
			append_redir(new, &temp);
		else if (temp->type == L_WORD)
			new->cmd_args = expand_searcher(&(new->cmd_args), temp->data, 1);
		temp = temp->next;
	}
	if (*head)
		(*last)->next = new;
	else
		*head = new;
	(*last) = new;
	if (temp && temp->type == L_PIPE)
		temp = temp->next;
	return (temp);
}

t_cmd	*parser(t_token *head)
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
	{
		temp = build_simple_cmd(&cmd_head, &cmd_last, temp);
	}
	print_cmd(cmd_head);
	return (cmd_head);
}
