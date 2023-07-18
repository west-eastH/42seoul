/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:22:24 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/17 14:34:55 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map(t_param *par)
{
	t_map	*cur;
	int		i;

	i = 0;
	cur = par->map;
	while (cur)
	{
		i = 0;
		while (i < par->wi_cnt)
		{
			if (cur->line[i] != 'C' && cur->line[i] != 'E'
				&& cur->line[i] != 'P' && cur->line[i] != '1'
				&& cur->line[i] != '0')
				return (1);
			i++;
		}
		cur = cur->next;
	}
	return (0);
}

int	nxy_check(int *nxy, char **map, char **vis)
{
	if (nxy[0] < 1 || nxy[0] >= nxy[2]
		|| nxy[1] < 1 || nxy[1] >= nxy[3])
		return (1);
	if (vis[nxy[1]][nxy[0]] == '1' || map[nxy[1]][nxy[0]] == '1')
		return (1);
	return (0);
}

void	set_cur(int *cur_x, int *cur_y, t_stack *stack)
{
	*cur_x = top_stack(stack)->x;
	*cur_y = top_stack(stack)->y;
}
