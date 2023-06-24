/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:41:50 by dongseo           #+#    #+#             */
/*   Updated: 2023/06/25 05:24:48 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	check_sort(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*cur;

	if (stack_b->size != 0)
	{
		ft_printf("KO\n");
		return ;
	}
	cur = stack_a->head->next;
	while (cur != stack_a->tail)
	{
		if (cur->next == stack_a->tail)
			break ;
		if (cur->data < cur->next->data)
		{
			ft_printf("KO\n");
			return ;
		}
		cur = cur->next;
	}
	ft_printf("OK\n");
}

int	is_rotate(char *command, t_stack *stack_a, t_stack *stack_b)
{
	if (ft_strncmp(command, "ra", ft_strlen(command) - 1) == 0)
		rotate(stack_a);
	else if (ft_strncmp(command, "rb", ft_strlen(command) - 1) == 0)
		rotate(stack_b);
	else if (ft_strncmp(command, "rr", ft_strlen(command) - 1) == 0)
	{
		rotate(stack_a);
		rotate(stack_b);
	}
	else if (ft_strncmp(command, "rra", ft_strlen(command) - 1) == 0)
		rev_rotate(stack_a);
	else if (ft_strncmp(command, "rrb", ft_strlen(command) - 1) == 0)
		rev_rotate(stack_b);
	else if (ft_strncmp(command, "rrr", ft_strlen(command) - 1) == 0)
	{
		rev_rotate(stack_a);
		rev_rotate(stack_b);
	}
	else
		return (1);
	return (0);
}

int	is_swap_or_push(char *command, t_stack *stack_a, t_stack *stack_b)
{
	if (ft_strncmp(command, "sa", ft_strlen(command) - 1) == 0)
		swap(stack_a);
	else if (ft_strncmp(command, "sb", ft_strlen(command) - 1) == 0)
		swap(stack_b);
	else if (ft_strncmp(command, "ss", ft_strlen(command) - 1) == 0)
	{
		swap(stack_a);
		swap(stack_b);
	}
	else if (ft_strncmp(command, "pa", ft_strlen(command) - 1) == 0)
		push_stack(stack_a, stack_b);
	else if (ft_strncmp(command, "pb", ft_strlen(command) - 1) == 0)
		push_stack(stack_b, stack_a);
	else
		return (1);
	return (0);
}

int	check_command(char *command, t_stack *stack_a, t_stack *stack_b)
{
	while (command)
	{
		if (command[0] == 's' || command[0] == 'p')
		{
			if (is_swap_or_push(command, stack_a, stack_b))
				return (1);
		}
		else if (command[0] == 'r')
		{
			if (is_rotate(command, stack_a, stack_b))
				return (1);
		}
		else
			return (1);
		free(command);
		ft_printf("stack_A : ");
		print_stack(stack_a);
		ft_printf("stack_B : ");
		print_stack(stack_b);
		command = get_next_line(0);
	}
	free(command);
	return (0);
}

int	main(int argc, char *argv[])
{
	char	*command;
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = (t_stack *)malloc(sizeof(t_stack));
	stack_b = (t_stack *)malloc(sizeof(t_stack));
	if (stack_init(argc, argv, stack_a, stack_b))
	{
		ft_printf("Error\n");
		exit(1);
	}
	command = get_next_line(0);
	if (check_command(command, stack_a, stack_b))
	{
		ft_printf("Error\n");
		command = NULL;
		free(command);
		exit(1);
	}
	check_sort(stack_a, stack_b);
	return (0);
}
