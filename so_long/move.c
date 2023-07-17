/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:28:33 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/17 13:51:46 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_exit(t_param *par, t_map *cur, int flag)
{
	if (check_end(par))
	{
		ft_printf("end\n");
		exit(0);
	}
	par->move++;
	ft_printf("move = %d\n", par->move);
	cur->line[par->p_x] = '0';
	if (flag == 1)
		par->p_y--;
	if (flag == 2)
		par->p_y++;
	if (flag == 3)
		par->p_x--;
	if (flag == 4)
		par->p_x++;
	draw_map(par);
}

void	move_right(t_param *par)
{
	t_map	*cur;
	int		i;

	mlx_clear_window(par->mlx, par->win);
	cur = par->map;
	i = 0;
	while (i++ < par->p_y)
		cur = cur->next;
	if (cur->line[par->p_x + 1] != '1')
	{
		if (cur->line[par->p_x + 1] == 'E')
		{
			move_exit(par, cur, 4);
			return ;
		}
		par->move++;
		ft_printf("move = %d\n", par->move);
		if (cur->line[par->p_x] != 'E')
			cur->line[par->p_x] = '0';
		cur->line[par->p_x + 1] = 'P';
		par->p_x++;
	}
	draw_map(par);
}

void	move_left(t_param *par)
{
	t_map	*cur;
	int		i;

	mlx_clear_window(par->mlx, par->win);
	cur = par->map;
	i = 0;
	while (i++ < par->p_y)
		cur = cur->next;
	if (cur->line[par->p_x - 1] != '1')
	{
		if (cur->line[par->p_x - 1] == 'E')
		{
			move_exit(par, cur, 3);
			return ;
		}
		par->move++;
		ft_printf("move = %d\n", par->move);
		if (cur->line[par->p_x] != 'E')
			cur->line[par->p_x] = '0';
		cur->line[par->p_x - 1] = 'P';
		par->p_x--;
	}
	draw_map(par);
}

void	move_up(t_param *par)
{
	t_map	*cur;
	int		i;

	mlx_clear_window(par->mlx, par->win);
	cur = par->map;
	i = 0;
	while (i++ < par->p_y)
		cur = cur->next;
	if (cur->pre == NULL)
		return ;
	if (cur->pre->line[par->p_x] != '1')
	{
		if (cur->pre->line[par->p_x] == 'E')
		{
			move_exit(par, cur, 1);
			return ;
		}
		par->move++;
		ft_printf("move = %d\n", par->move);
		if (cur->line[par->p_x] != 'E')
			cur->line[par->p_x] = '0';
		cur->pre->line[par->p_x] = 'P';
		par->p_y--;
	}
	draw_map(par);
}

void	move_down(t_param *par)
{
	t_map	*cur;
	int		i;

	mlx_clear_window(par->mlx, par->win);
	cur = par->map;
	i = 0;
	while (i++ < par->p_y)
		cur = cur->next;
	if (cur->next == NULL)
		return ;
	if (cur->next->line[par->p_x] != '1')
	{
		if (cur->next->line[par->p_x] == 'E')
		{
			move_exit(par, cur, 2);
			return ;
		}
		par->move++;
		ft_printf("move = %d\n", par->move);
		if (cur->line[par->p_x] != 'E')
			cur->line[par->p_x] = '0';
		cur->next->line[par->p_x] = 'P';
		par->p_y++;
	}
	draw_map(par);
}
