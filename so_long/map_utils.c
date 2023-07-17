/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:41:29 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/17 13:50:51 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map(t_param *par, t_map *cur)
{
	int	i;

	i = 0;
	while (i < par->wi_cnt)
	{
		mlx_put_image_to_window(par->mlx, par->win, par->g, par->x, par->y);
		if (cur->line[i] == '1')
			mlx_put_image_to_window(par->mlx, par->win, par->w, par->x, par->y);
		if (cur->line[i] == 'E')
		{
			if (check_end(par))
				mlx_put_image_to_window(par->mlx, par->win,
					par->e2, par->x, par->y);
			else
				mlx_put_image_to_window(par->mlx, par->win,
					par->e1, par->x, par->y);
		}
		if (cur->line[i] == 'C')
			mlx_put_image_to_window(par->mlx, par->win, par->c, par->x, par->y);
		par->x += par->img_wi;
		i++;
	}
}

void	draw_map(t_param *par)
{
	int		i;
	int		j;
	t_map	*cur;

	i = 0;
	cur = par->map;
	while (i < par->he_cnt)
	{
		j = 0;
		read_map(par, cur);
		par->x = 0;
		par->y += par->img_he;
		cur = cur->next;
		i++;
	}
	mlx_put_image_to_window(par->mlx, par->win, par->p,
		par->p_x * par->img_wi, par->p_y * par->img_he);
	par->x = 0;
	par->y = 0;
}

char	**map_cpy(t_param *par)
{
	char	**result;
	int		i;
	t_map	*cur;

	cur = par->map;
	i = 0;
	result = (char **)malloc(sizeof(char *) * (par->he_cnt + 1));
	if (!result)
		exit(1);
	while (i < par->he_cnt)
	{
		result[i] = ft_strdup(cur->line);
		if (!result[i])
			exit(1);
		cur = cur->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	*make_empty_str(char *st)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)malloc(ft_strlen(st) + 1);
	while (st[i])
	{
		result[i] = '0';
		i++;
	}
	result[i] = 0;
	return (result);
}

void	set_dxy(int *dx, int *dy)
{
	dx[0] = 1;
	dx[1] = 0;
	dx[2] = -1;
	dx[3] = 0;
	dy[0] = 0;
	dy[1] = 1;
	dy[2] = 0;
	dy[3] = -1;
}
