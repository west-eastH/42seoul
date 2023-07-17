/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:43:44 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/17 13:36:39 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init(t_param *par)
{
	par->fd = open("map/map.ber", O_RDONLY);
	par->mlx = mlx_init();
	par->x = 0;
	par->y = 0;
	par->move = 0;
	par->c = mlx_xpm_file_to_image(par->mlx,
			"img/c.xpm", &par->img_wi, &par->img_he);
	par->g = mlx_xpm_file_to_image(par->mlx,
			"img/g.xpm", &par->img_wi, &par->img_he);
	par->w = mlx_xpm_file_to_image(par->mlx,
			"img/w.xpm", &par->img_wi, &par->img_he);
	par->p = mlx_xpm_file_to_image(par->mlx,
			"img/p.xpm", &par->img_wi, &par->img_he);
	par->e1 = mlx_xpm_file_to_image(par->mlx,
			"img/e1.xpm", &par->img_wi, &par->img_he);
	par->e2 = mlx_xpm_file_to_image(par->mlx,
			"img/e2.xpm", &par->img_wi, &par->img_he);
	par->map = NULL;
}

int	is_border(t_param *par, int wi)
{
	t_map	*cur;
	int		i;

	i = 0;
	cur = par->map;
	while (cur)
	{
		i = 0;
		if (cur == par->map || cur->next == NULL)
		{
			while (i < wi)
			{
				if (cur->line[i] != '1')
					return (1);
				i++;
			}
		}
		else
		{
			if (cur->line[0] != '1' || cur->line[wi - 1] != '1')
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}

int	is_rectangle(t_param *par, int wi)
{
	t_map	*cur;
	int		cur_len;

	cur = par->map;
	while (cur)
	{
		cur_len = ft_strlen(cur->line) - 1;
		if (cur_len != wi || (cur->next == NULL && cur_len + 1 != wi))
		{
			if (cur->next == NULL && cur_len + 1 == wi)
			{
				cur = cur->next;
				continue ;
			}
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

void	min_pec_check(t_param *par, int *p, int *e, int *c)
{
	t_map	*cur;
	int		i;
	int		p_he;

	p_he = 0;
	cur = par->map;
	while (cur)
	{
		i = 0;
		while (i++ < par->wi_cnt)
		{
			if (cur->line[i - 1] == 'P')
			{
				*p += 1;
				par->p_x = i - 1;
				par->p_y = p_he;
			}
			if (cur->line[i - 1] == 'E')
				*e += 1;
			if (cur->line[i - 1] == 'C')
				*c += 1;
		}
		cur = cur->next;
		p_he++;
	}
}

int	check_end(t_param *par)
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
			if (cur->line[i] == 'C')
				return (0);
			i++;
		}
		cur = cur->next;
	}
	return (1);
}
