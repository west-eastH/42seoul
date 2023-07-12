#include "mlx.h"
#include "so_long.h"

#include <stdio.h>
#include <stdlib.h>


#define KEY_ESC			53
#define KEY_W				13
#define KEY_S				1
#define KEY_A				0
#define KEY_D				2
#define PRESS_RED_BUTTON	17

void	init(t_param *par)
{
	par->fd = open("map/map.ber", O_RDONLY);
	par->mlx = mlx_init();
	par->x = 0;
	par->y = 0;
	par->move = 0;
	par->c = mlx_xpm_file_to_image(par->mlx, "img/c.xpm", &par->img_wi, &par->img_he);
	par->g = mlx_xpm_file_to_image(par->mlx, "img/g.xpm", &par->img_wi, &par->img_he);
	par->w = mlx_xpm_file_to_image(par->mlx, "img/w.xpm", &par->img_wi, &par->img_he);
	par->p = mlx_xpm_file_to_image(par->mlx, "img/p.xpm", &par->img_wi, &par->img_he);
	par->e = mlx_xpm_file_to_image(par->mlx, "img/e1.xpm", &par->img_wi, &par->img_he);
	par->map = NULL;
}

void map_init(t_param *par)
{
	t_map	*cur;
	char	*st;

	cur = (t_map *)malloc(sizeof(t_map));
	if (!cur)
		exit(1);
	par->map = cur;
	st = get_next_line(par->fd);
	while (st)
	{
		cur->line = st;
		cur->next = (t_map *)malloc(sizeof(t_map));
		if (!cur->next)
			exit(1);
		free(st);
		st = get_next_line(par->fd);
		cur = cur->next;
		cur->next = NULL;
	}
	free(st);
	cur = par->map;
	while (cur)
	{
		printf("%s", cur->line);
		cur = cur->next;
	}
}

int	main(void)
{
	t_param		par;

	init(&par);
	if (par.fd < 0)
		return (0);
	printf("qqqqqqqqqqqqqqq\n");
	par.win = mlx_new_window(par.mlx, par.img_wi * 8, par.img_he * 5, "so_long");
	printf("qqqqqqqqqqqqqqq\n");
	map_init(&par);
	printf("qqqqqqqqqqqqqqq\n");
	int i;
	int j;
	i = 0;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 8)
		{
			mlx_put_image_to_window(par.mlx, par.win, par.g, par.x, par.y);
			par.x += par.img_wi;
			j++;
		}
		par.x = 0;
		par.y += par.img_he;
		i++;
	}
	mlx_loop(par.mlx);
	return (0);
}