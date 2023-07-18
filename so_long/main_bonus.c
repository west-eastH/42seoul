/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:35:03 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/18 18:05:05 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

#define KEY_ESC			53
#define KEY_W				13
#define KEY_S				1
#define KEY_A				0
#define KEY_D				2
#define PRESS_RED_BUTTON	17

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

int	frame(t_param *par)
{
	char	*move_str;

	move_str = move_print(par);
	par->frame = par->frame % 44;
	par->frame += 1;
	monster_frame(par);
	player_frame(par);
	draw_map(par);
	mlx_string_put(par->mlx, par->win, 50, 50, 0x00FF0000, move_str);
	free(move_str);
	return (0);
}

int	main(void)
{
	t_param		par;

	init(&par);
	if (par.fd <= 0)
		return (0);
	if (map_init(&par))
	{
		ft_printf("Error\n");
		ft_printf("Map Error\n");
		free_map(par.map);
		return (0);
	}
	mlx_key_hook(par.win, key_hook, &par);
	mlx_hook(par.win, PRESS_RED_BUTTON, 0, ft_close, 0);
	mlx_loop_hook(par.mlx, frame, &par);
	mlx_loop(par.mlx);
	return (0);
}
