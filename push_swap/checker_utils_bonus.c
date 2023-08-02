/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:57:22 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/02 21:35:03 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	free_stack(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a)
		free(stack_a);
	if (stack_b)
		free(stack_b);
}

int	check_swap(char *command, t_stack *stack_a, t_stack *stack_b)
{
	if (ft_strncmp(command, "sa\n", 4) == 0)
		swap(stack_a, 0);
	else if (ft_strncmp(command, "sb\n", 4) == 0)
		swap(stack_b, 0);
	else if (ft_strncmp(command, "ss\n", 4) == 0)
	{
		swap(stack_a, 0);
		swap(stack_b, 0);
	}
	else
		return (1);
	return (0);
}

int	check_push(char *command, t_stack *stack_a, t_stack *stack_b)
{
	if (ft_strncmp(command, "pa\n", 4) == 0)
		push_stack(stack_a, stack_b, 0);
	else if (ft_strncmp(command, "pb\n", 4) == 0)
		push_stack(stack_b, stack_a, 0);
	else
		return (1);
	return (0);
}

int	check_rotate(char *command, t_stack *stack_a, t_stack *stack_b)
{
	if (ft_strncmp(command, "ra\n", 4) == 0)
		rotate(stack_a, 0);
	else if (ft_strncmp(command, "rb\n", 4) == 0)
		rotate(stack_b, 0);
	else if (ft_strncmp(command, "rr\n", 4) == 0)
	{
		rotate(stack_a, 0);
		rotate(stack_b, 0);
	}
	else if (ft_strncmp(command, "rra\n", 5) == 0)
		rev_rotate(stack_a, 0);
	else if (ft_strncmp(command, "rrb\n", 5) == 0)
		rev_rotate(stack_b, 0);
	else if (ft_strncmp(command, "rrr\n", 5) == 0)
	{
		rev_rotate(stack_a, 0);
		rev_rotate(stack_b, 0);
	}
	else
		return (1);
	return (0);
}

void	check_sort(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*cur;

	if (stack_b->size != 0)
	{
		ft_printf("KO\n");
		return ;
	}
	cur = stack_a->tail->pre;
	while (cur != stack_a->head->next)
	{
		if (cur->data > cur->pre->data)
		{
			ft_printf("KO\n");
			return ;
		}
		cur = cur->pre;
	}
	ft_printf("OK\n");
}
