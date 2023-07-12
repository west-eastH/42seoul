/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:12:41 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/12 16:55:17 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
}	t_map;

typedef struct s_param
{
	void	*mlx;
	void	*win;
	void	*c;
	void	*g;
	void	*w;
	void	*p;
	void	*e;
	int		fd;
	int		x;
	int		y;
	int		p_x;
	int		p_y;
	int		img_wi;
	int		img_he;
	int		win_wi;
	int		win_he;
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


size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2, size_t s2_len);
long long	ft_atoi(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

/////////////////////////////////////////////////////////
#endif