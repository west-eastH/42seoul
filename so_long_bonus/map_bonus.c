/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:44:35 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/18 18:05:10 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	push_map(t_param *par, char *st)
{
	t_map	*temp;
	t_map	*cur;

	temp = (t_map *)malloc(sizeof(t_map));
	if (!temp)
		exit(1);
	temp->line = ft_strdup(st);
	if (!temp->line)
		exit(1);
	temp->pre = NULL;
	temp->next = NULL;
	if (par->map == NULL)
	{
		par->map = temp;
		return ;
	}
	cur = par->map;
	while (cur->next)
		cur = cur->next;
	cur->next = temp;
	temp->pre = cur;
	return ;
}

int	map_init(t_param *par)
{
	char	*st;
	int		he;
	t_map	*cur;

	st = get_next_line(par->fd);
	while (st)
	{
		push_map(par, st);
		free(st);
		st = get_next_line(par->fd);
	}
	free(st);
	cur = par->map;
	he = 1;
	while (cur->next)
	{
		he++;
		cur = cur->next;
	}
	par->win_wi = par->img_wi * (ft_strlen(par->map->line) - 1);
	par->win_he = par->img_he * he;
	return (map_error_check(par, ft_strlen(par->map->line) - 1, he));
}

int	route_check(t_param *par, char **map)
{
	char	**vis;
	int		i;
	t_stack	*stack;
	int		nxy[4];
	int		result;

	stack = NULL;
	nxy[2] = par->wi_cnt - 1;
	nxy[3] = par->he_cnt - 1;
	i = 0;
	vis = (char **)malloc(sizeof(char *) * (par->he_cnt + 1));
	if (!vis)
		exit(1);
	while (i < par->he_cnt)
	{
		vis[i] = make_empty_str(par->map->line);
		i++;
	}
	vis[i] = NULL;
	vis[par->p_y][par->p_x] = '1';
	push_back(&stack, par->p_y, par->p_x);
	result = dfs(&stack, map, vis, nxy);
	free_copy_map(vis);
	free_copy_map(map);
	return (result);
}

int	map_error_check(t_param *par, int wi, int he)
{
	int		p;
	int		e;
	int		c;
	char	**copy_map;

	p = 0;
	e = 0;
	c = 0;
	par->wi_cnt = wi;
	par->he_cnt = he;
	if (is_border(par, wi) || wi < 3 || he < 3
		|| is_rectangle(par, wi) || check_map(par))
		return (1);
	min_pec_check(par, &p, &e, &c);
	copy_map = map_cpy(par);
	if (p != 1 || e != 1 || c < 1 || route_check(par, copy_map))
		return (1);
	par->win = mlx_new_window(par->mlx, par->win_wi, par->win_he, "so_long");
	draw_map(par);
	return (0);
}

int	dfs(t_stack **stack, char **map, char **vis, int *nxy)
{
	int		dx[4];
	int		dy[4];
	int		cur_x;
	int		cur_y;
	int		dir;

	set_dxy(dx, dy);
	while (!is_empty(*stack))
	{
		set_cur(&cur_x, &cur_y, *stack);
		pop_stack(stack);
		dir = 0;
		while (dir++ < 4)
		{
			nxy[0] = cur_x + dx[dir - 1];
			nxy[1] = cur_y + dy[dir - 1];
			if (nxy_check(nxy, map, vis))
				continue ;
			if (map[nxy[1]][nxy[0]] == 'E')
				return (0);
			vis[nxy[1]][nxy[0]] = '1';
			push_back(stack, nxy[1], nxy[0]);
		}
	}
	return (1);
}
