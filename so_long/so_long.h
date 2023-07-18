/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:12:41 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/18 19:36:35 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include "mlx.h"

typedef struct s_map
{
	char			*line;
	struct s_map	*pre;
	struct s_map	*next;
}	t_map;

typedef struct s_stack
{
	int				x;
	int				y;
	struct s_stack	*pre;
	struct s_stack	*next;
}	t_stack;

typedef struct s_param
{
	void	*mlx;
	void	*win;
	void	*c;
	void	*g;
	void	*w;
	void	*p;
	void	*e1;
	void	*e2;
	int		fd;
	int		x;
	int		y;
	int		p_x;
	int		p_y;
	int		img_wi;
	int		img_he;
	int		win_wi;
	int		win_he;
	int		wi_cnt;
	int		he_cnt;
	int		move;
	t_map	*map;
}	t_param;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	int				fd;
	char			*st;
	struct s_list	*next;
}t_list;

size_t				gnl_ft_strlen(const char *s);
char				*gnl_ft_strdup(char *s1, size_t len);
char				*gnl_ft_strjoin(char *s1, char *s2, size_t s2_len);
t_list				*gnl_ft_find_fd(t_list *lst, int fd);
int					gnl_ft_backup(t_list **lst, int fd, char *buffer, int size);
int					gnl_is_line(char *backup);
char				*gnl_split(int fd, t_list **lst, int idx);
char				*gnl_no_line(int fd, t_list **lst, int size);
char				*get_next_line(int fd);
void				gnl_ft_free(t_list **lst, int fd);

ssize_t				st_len(const char *st);
void				ft_putnbr_di(int n, ssize_t *len);
void				ft_putnbr_u(unsigned int u, ssize_t *len);
void				ft_putnbr_x(unsigned int x, ssize_t *len, int is_upper);
unsigned long long	set_base(int base[], unsigned long long p);
ssize_t				ft_printf_c(char c);
ssize_t				ft_printf_s(char *s);
ssize_t				ft_printf_di(int d);
ssize_t				ft_printf_u(unsigned int u);
ssize_t				ft_printf_x(int x, int is_upper);
ssize_t				ft_printf_p(unsigned long long p);
ssize_t				check_format(char format, va_list *ap);
int					ft_printf(const char *st, ...);

size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

void				move_exit(t_param *par, t_map *cur, int flag);
void				move_right(t_param *par);
void				move_left(t_param *par);
void				move_up(t_param *par);
void				move_down(t_param *par);

void				push_map(t_param *par, char *st);
int					map_init(t_param *par);
int					route_check(t_param *par, char **map);
int					map_error_check(t_param *par, int wi, int he);
int					dfs(t_stack **stack, char **map, char **vis, int *nxy);

void				read_map(t_param *par, t_map *cur);
void				draw_map(t_param *par);
char				**map_cpy(t_param *par);
char				*make_empty_str(char *st);
void				set_dxy(int *dx, int *dy);

void				push_back(t_stack **stack, int y, int x);
int					is_empty(t_stack *stack);
t_stack				*top_stack(t_stack *stack);
int					stack_size(t_stack *stack);
void				pop_stack(t_stack **stack);

void				init(t_param *par);
int					is_border(t_param *par, int wi);
int					is_rectangle(t_param *par, int wi);
void				min_pec_check(t_param *par, int *p, int *e, int *c);
int					check_end(t_param *par);

void				free_map(t_map *map);
void				free_copy_map(char	**map);
int					key_hook(int keycode, t_param *par);
int					ft_close(void);
int					check_map(t_param *par);
int					nxy_check(int *nxy, char **map, char **vis);
void				set_cur(int *cur_x, int *cur_y, t_stack *stack);
#endif