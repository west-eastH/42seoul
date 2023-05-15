/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:52:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/15 21:53:06 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include <unistd.h>

typedef struct s_node
{
	int		data;
	int		rank;
	struct s_node	*pre;
	struct s_node	*next;
}t_node;

typedef struct s_stack
{
	int		size;
	t_node	*head;
	t_node	*tail;
}t_stack;

#endif