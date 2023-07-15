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

int push_map(t_param *par, char *st)
{
	t_map *temp;
	t_map *cur;

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
		return (0);
	}
	cur = par->map;
	while (cur->next)
		cur = cur->next;
	cur->next = temp;
	temp->pre = cur;
	return (0);
}

int	is_border(t_param *par, int wi)
{
	t_map *cur;
	int i;

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
					return 1;
				i++;
			}
		}
		else
		{
			if (cur->line[0] != '1' || cur->line[wi - 1] != '1')
					return 1;
		}
		cur = cur->next;
	}
	return 0;
}

int is_rectangle(t_param *par, int wi)
{
	t_map *cur;
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
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

void min_pec_check(t_param *par, int *p, int *e, int *c)
{
	t_map *cur;
	int i;
	int	p_he;

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

void read_map(t_param *par, t_map *cur)
{
	int i;

	i = 0;
	while (i < par->wi_cnt)
	{
		mlx_put_image_to_window(par->mlx, par->win, par->g, par->x, par->y);
		if (cur->line[i] == '1')
			mlx_put_image_to_window(par->mlx, par->win, par->w, par->x, par->y);
		if (cur->line[i] == 'E')
			mlx_put_image_to_window(par->mlx, par->win, par->e, par->x, par->y);
		if (cur->line[i] == 'C')
			mlx_put_image_to_window(par->mlx, par->win, par->c, par->x, par->y);
		par->x += par->img_wi;
		i++;
	}
}

void draw_map(t_param *par)
{
	int i;
	int j;
	t_map *cur;
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

char **map_cpy(t_param *par)
{
	char **result;
	int	i;
	t_map *cur;

	ft_printf("wwwww");
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
	return result;
}
char *make_empty_str(char *st)
{
	char *result;
	int i;

	i = 0;
	result = (char *)malloc(ft_strlen(st) + 1);
	while (st[i])
	{
		result[i] = '0';
		i++;
	}
	result[i] = 0;
	return result;
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

void	push_back(t_stack **stack, int y, int x)
{
	t_stack *cur;
	t_stack *temp;

	cur = (t_stack *)malloc(sizeof(t_stack));
	if (!cur)
		exit(1);
	cur->x = x;
	cur->y = y;
	cur->pre = NULL;
	cur->next = NULL;
	if (*stack == NULL)
	{
		*stack = cur;
		return ;
	}
	temp = *stack;
	while (temp->next)
		temp = temp->next;
	cur->pre = temp;
	temp->next = cur;
}

int is_empty(t_stack *stack)
{
	if (stack == NULL)
		return 1;
	return 0;
}

t_stack *top_stack(t_stack *stack)
{
	t_stack *cur;

	cur = stack;
	while (cur->next)
		cur = cur->next;
	return cur;
}

int	stack_size(t_stack *stack)
{
	t_stack *cur;
	int i;

	if (stack == NULL)
		return 0;
	i = 1;
	cur = stack;
	while(cur->next)
	{
		i++;
		cur = cur->next;
	}
	return i;
}
void	pop_stack(t_stack **stack)
{
	t_stack *cur;
	t_stack *temp;
	if (stack_size(*stack) == 1)
	{
		cur = *stack;
		free(cur);
		*stack = NULL;
		return ;
	}
	cur = *stack;
	while (cur->next)
		cur = cur->next;
	temp = cur;
	cur->pre->next = NULL;
	free(temp);
	temp = NULL;
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
		cur_x = top_stack(*stack)->x;
		cur_y = top_stack(*stack)->y;
		printf("cur_x = %d cur_y = %d\n", cur_x, cur_y);
		pop_stack(stack);
		dir = 0;
		while (dir < 4)
		{
			nxy[0] = cur_x + dx[dir];
			nxy[1] = cur_y + dy[dir];
			if (nxy[0] < 1 || nxy[0] >= nxy[2] || nxy[1] < 1 || nxy[1] >= nxy[3])
			{
				printf("nx = %d wi = %d ny = %d he = %d\n", nxy[0], nxy[2], nxy[1], nxy[3]);
				dir++;
				continue;
			}
			if (vis[nxy[1]][nxy[0]] == '1' || map[nxy[1]][nxy[0]] == '1')
			{
				printf("nx = %d ny = %d\n", nxy[0], nxy[1]);
				printf("vis[%d][%d] = %c  map[%d][%d] = %c\n", nxy[1], nxy[0], vis[nxy[1]][nxy[0]], nxy[1], nxy[0], map[nxy[1]][nxy[0]]);
				dir++;
				continue;
			}
			vis[nxy[1]][nxy[0]] = '1';
			push_back(stack, nxy[1], nxy[0]);
		}
	}
	return 0;
}

int route_check(t_param *par, char **map)
{
	char	**vis;
	int		i;
	t_stack	*stack;
	int		nxy[4];

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
	dfs(&stack, map, vis, nxy);
	return 0;
}

int	map_error_check(t_param *par, int wi, int he)
{
	int p;
	int e;
	int c;
	char **copy_map;

	p = 0;
	e = 0;
	c = 0;
	par->wi_cnt = wi;
	par->he_cnt = he;
	if (is_border(par, wi) || wi < 3 || he < 3 || is_rectangle(par, wi))
		return 1;
	min_pec_check(par, &p, &e, &c);
	copy_map = map_cpy(par);
	if (p != 1 || e != 1 || c < 1 || route_check(par, copy_map))
		return 1;
	par->win = mlx_new_window(par->mlx, par->win_wi, par->win_he, "so_long");
	draw_map(par);
	return 0;

}

int map_init(t_param *par)
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
	if (par->map == NULL)
		return (1);
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

int check_end(t_param *par)
{
	t_map *cur;
	int i;

	i = 0;
	cur = par->map;
	while (cur)
	{
		i = 0;
		while (i < par->wi_cnt)
		{
			if (cur->line[i] == 'C')
				return 0;
			i++;
		}
		cur = cur->next;
	}
	return (1);
}
void move_exit(t_param *par, t_map *cur, int flag)
{
	if (check_end(par))
	{
		ft_printf("end\n");
		exit(0);
	}
	par->move++;
	ft_printf("move = %d\n",par->move);
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

void move_right(t_param *par)
{
	t_map *cur;
	int i;
	int j;

	mlx_clear_window(par->mlx, par->win);
	cur = par->map;
	i = 0;
	j = 0;
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
		ft_printf("move = %d\n",par->move);
		if (cur->line[par->p_x] != 'E')
			cur->line[par->p_x] = '0';
		cur->line[par->p_x + 1] = 'P';
		par->p_x++;
	}
	draw_map(par);
}

void move_left(t_param *par)
{
	t_map *cur;
	int i;
	int j;

	mlx_clear_window(par->mlx, par->win);
	cur = par->map;
	i = 0;
	j = 0;
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
		ft_printf("move = %d\n",par->move);
		if (cur->line[par->p_x] != 'E')
			cur->line[par->p_x] = '0';
		cur->line[par->p_x - 1] = 'P';
		par->p_x--;
	}
	draw_map(par);
}

void move_up(t_param *par)
{
	t_map *cur;
	int i;
	int j;

	mlx_clear_window(par->mlx, par->win);
	cur = par->map;
	i = 0;
	j = 0;
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
		ft_printf("move = %d\n",par->move);
		if (cur->line[par->p_x] != 'E')
			cur->line[par->p_x] = '0';
		cur->pre->line[par->p_x] = 'P';
		par->p_y--;
	}
	draw_map(par);
}

void move_down(t_param *par)
{
	t_map *cur;
	int i;
	int j;

	mlx_clear_window(par->mlx, par->win);
	cur = par->map;
	i = 0;
	j = 0;
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
		ft_printf("move = %d\n",par->move);
		if (cur->line[par->p_x] != 'E')
			cur->line[par->p_x] = '0';
		cur->next->line[par->p_x] = 'P';
		par->p_y++;
	}
	draw_map(par);
}
int key_hook(int keycode, t_param *par)
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
	return 0;
}
int ft_close(void)
{
	exit(0);
}

int	main(void)
{
	t_param		par;

	init(&par);
	if (par.fd < 0)
		return (0);
	map_init(&par);
	ft_printf("move = %d\n", par.move);
	mlx_key_hook(par.win, key_hook, &par);
	mlx_hook(par.win, PRESS_RED_BUTTON, 0, ft_close, 0);
	mlx_loop(par.mlx);
	return (0);
}