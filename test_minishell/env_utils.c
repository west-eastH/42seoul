/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:34:22 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/25 11:31:15 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node(t_package *pack, char *name, char *value);
void	add_sorted_node(t_env	**head, t_env *new);

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
		idx++;
	}
}

t_env	*find_env(char *name)
{
	t_env *temp;

	temp = g_package.origin_head;
	while (temp && (ft_strncmp(temp->name, name, ft_strlen(name))
			|| temp->name[ft_strlen(name)]))
		temp = temp->origin_next;
	return (temp);
}

void	add_env_node(t_package *pack, char *name, char *value)
{
	t_env	*new;

	new = find_env(name);
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
	new->value = ft_strdup(value);
	new->origin_next = 0;
	new->sorted_next = 0;
	new->origin_prev = 0;
	new->sorted_prev = 0;
	if (!(pack->origin_head))
	{
		pack->origin_head = new;
		pack->origin_last = new;
		pack->sorted_head = new;
	}
	else
	{
		new->origin_prev = pack->origin_last;
		pack->origin_last->origin_next = new;
		pack->origin_last = new;
		add_sorted_node(&(pack->sorted_head), new);
	}
}

void	add_sorted_node(t_env	**head, t_env *new)
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

void	delete_env(char *name)
{
	t_env	*target;
	t_env	*prev;

	target = find_env(name);
	if (!target)
		return ;
	prev = target->origin_prev;
	if (prev)
		prev->origin_next = target->origin_next;
	else
		g_package.origin_head = target->origin_next;
	if (target->origin_next)
		target->origin_next->origin_prev = prev;
	prev = target->sorted_prev;
	if (prev)
		prev->sorted_next = target->sorted_next;
	else
		g_package.sorted_head = target->sorted_next;
	if (target->sorted_next)
		target->sorted_next->sorted_prev = prev;
	free(target->name);
	if (target->value)
		free(target->value);
	free(target);
}
