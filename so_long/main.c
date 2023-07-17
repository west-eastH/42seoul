/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:35:03 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/17 13:50:41 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define KEY_ESC			53
#define KEY_W				13
#define KEY_S				1
#define KEY_A				0
#define KEY_D				2
#define PRESS_RED_BUTTON	17

void	free_map(t_map *map)
{
	t_map	*cur;
	t_map	*temp;

	cur = map;
	if (cur == NULL)
		return ;
	while (cur)
	{
		temp = cur->next;
		free(cur->line);
		cur->line = NULL;
		free(cur);
		cur = temp;
	}
}

void	free_copy_map(char	**map)
{
	int		i;
	char	*temp;

	i = 0;
	while (map[i])
	{
		temp = map[i];
		free(temp);
		temp = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

int	key_hook(int keycode, t_param *par)
{
	if (keycode == 53)
	{
		mlx_destroy_window(par->mlx, par->win);
		exit(0);
	}
	if (keycode == KEY_D)
		move_right(par);
	if (keycode == KEY_A)
		move_left(par);
	if (keycode == KEY_W)
		move_up(par);
	if (keycode == KEY_S)
		move_down(par);
	return (0);
}

int	ft_close(void)
{
	exit(0);
}

int	main(void)
{
	t_param		par;

	init(&par);
	if (par.fd < 0)
		return (0);
	if (map_init(&par))
	{
		free_map(par.map);
		ft_printf("Error\n");
		ft_printf("Map error\n");
		return (0);
	}
	ft_printf("move = %d\n", par.move);
	mlx_key_hook(par.win, key_hook, &par);
	mlx_hook(par.win, PRESS_RED_BUTTON, 0, ft_close, 0);
	mlx_loop(par.mlx);
	return (0);
}
