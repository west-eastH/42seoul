/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:34:22 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/03 13:59:21 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env(char *name, t_package *package)
{
	t_env	*temp;

	temp = package->sorted_head;
	while (temp && (ft_strncmp(temp->name, name, ft_strlen(name) + 1)))
		temp = temp->sorted_next;
	return (temp);
}

void	delete_env(char *name, t_package *package)
{
	t_env	*target;
	t_env	*prev;

	target = find_env(name, package);
	if (!target)
		return ;
	prev = target->origin_prev;
	if (prev)
		prev->origin_next = target->origin_next;
	else
		package->origin_head = target->origin_next;
	if (target->origin_next)
		target->origin_next->origin_prev = prev;
	if (!target->origin_next)
		package->origin_last = target->origin_prev;
	prev = target->sorted_prev;
	if (prev)
		prev->sorted_next = target->sorted_next;
	else
		package->sorted_head = target->sorted_next;
	if (target->sorted_next)
		target->sorted_next->sorted_prev = prev;
	free(target->name);
	free(target->value);
	free(target);
}

void	set_new_env(t_package *pack, t_env *new)
{
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
