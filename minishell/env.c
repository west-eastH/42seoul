/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:35:23 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/04 16:24:59 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(char **envp, t_package *package)
{
	int		idx;
	char	*temp;

	idx = 0;
	while (envp[idx])
	{
		temp = ft_strchr(envp[idx], '=');
		*temp = 0;
		add_env_node(package, envp[idx], temp + 1);
		*temp = '=';
		idx++;
	}
	idx = 0;
}

void	add_env_node(t_package *pack, char *name, char *value)
{
	t_env	*new;

	new = find_env(name, pack);
	if (new)
	{
		if (!value)
			return ;
		free(new->value);
		new->value = ft_strdup(value);
		return ;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		exit(1);
	new->name = ft_strdup(name);
	if (!new->name)
		exit(1);
	new->value = ft_strdup(value);
	set_new_env(pack, new);
}

void	add_sorted_node(t_env **head, t_env *new)
{
	t_env	*temp;
	t_env	*temp_next;

	temp = *head;
	if (ft_strcmp(new->name, temp->name) < 0)
	{
		*head = new;
		new->sorted_next = temp;
		temp->sorted_prev = new;
		return ;
	}
	while (temp->sorted_next && \
	ft_strcmp(new->name, temp->sorted_next->name) > 0)
		temp = temp->sorted_next;
	temp_next = temp->sorted_next;
	temp->sorted_next = new;
	if (temp_next)
		temp_next->sorted_prev = new;
	new->sorted_prev = temp;
	new->sorted_next = temp_next;
}
