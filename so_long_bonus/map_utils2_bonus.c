/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:22:24 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/18 18:05:17 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
				&& cur->line[i] != '0' && cur->line[i] != 'M')
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

void	monster_frame(t_param *par)
{
	if (par->frame / 4 == 0)
		par->m = mlx_xpm_file_to_image(par->mlx,
				"img/m1.xpm", &par->img_wi, &par->img_he);
	else if (par->frame / 4 == 1 || par->frame / 4 == 11)
		par->m = mlx_xpm_file_to_image(par->mlx,
				"img/m2.xpm", &par->img_wi, &par->img_he);
	else if (par->frame / 4 == 2 || par->frame / 4 == 10)
		par->m = mlx_xpm_file_to_image(par->mlx,
				"img/m3.xpm", &par->img_wi, &par->img_he);
	else if (par->frame / 4 == 3 || par->frame / 4 == 9)
		par->m = mlx_xpm_file_to_image(par->mlx,
				"img/m4.xpm", &par->img_wi, &par->img_he);
	else if (par->frame / 4 == 4 || par->frame / 4 == 8)
		par->m = mlx_xpm_file_to_image(par->mlx,
				"img/m5.xpm", &par->img_wi, &par->img_he);
	else if (par->frame / 4 == 5 || par->frame / 4 == 7)
		par->m = mlx_xpm_file_to_image(par->mlx,
				"img/m6.xpm", &par->img_wi, &par->img_he);
	else
	{
		par->m = mlx_xpm_file_to_image(par->mlx,
				"img/m7.xpm", &par->img_wi, &par->img_he);
	}
}

void	player_frame(t_param *par)
{
	if (par->frame / 4 == 0)
		par->p = mlx_xpm_file_to_image(par->mlx,
				"img/p1.xpm", &par->img_wi, &par->img_he);
	else if (par->frame / 4 == 1 || par->frame / 4 == 11)
		par->p = mlx_xpm_file_to_image(par->mlx,
				"img/p2.xpm", &par->img_wi, &par->img_he);
	else if (par->frame / 4 == 2 || par->frame / 4 == 10)
		par->p = mlx_xpm_file_to_image(par->mlx,
				"img/p3.xpm", &par->img_wi, &par->img_he);
	else if (par->frame / 4 == 3 || par->frame / 4 == 9)
		par->p = mlx_xpm_file_to_image(par->mlx,
				"img/p4.xpm", &par->img_wi, &par->img_he);
	else if (par->frame / 4 == 4 || par->frame / 4 == 8)
		par->p = mlx_xpm_file_to_image(par->mlx,
				"img/p5.xpm", &par->img_wi, &par->img_he);
	else if (par->frame / 4 == 5 || par->frame / 4 == 7)
		par->p = mlx_xpm_file_to_image(par->mlx,
				"img/p6.xpm", &par->img_wi, &par->img_he);
	else
	{
		par->p = mlx_xpm_file_to_image(par->mlx,
				"img/p7.xpm", &par->img_wi, &par->img_he);
	}
}
