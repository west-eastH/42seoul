/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:12:41 by dongseo           #+#    #+#             */
/*   Updated: 2023/06/25 05:58:15 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>


//ft_printf
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


//get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	int				fd;
	char			*st;
	struct s_list	*next;
}t_list;

char	*gnl_ft_strdup(char *s1, size_t len);
char	*gnl_ft_strjoin(char *s1, char *s2, size_t s2_len);
t_list	*ft_find_fd(t_list *lst, int fd);
int		ft_backup(t_list **lst, int fd, char *buffer, int size);
int		is_line(char *backup);
char	*gnl_split(int fd, t_list **lst, int idx);
char	*no_line(int fd, t_list **lst, int size);
char	*get_next_line(int fd);
void	ft_free(t_list **lst, int fd);


//ft_split
char	*ft_init(char *s_cpy, char c, size_t len, size_t *word_cnt);
void	set_index(size_t index[]);
int	make_result(char **result, char *s_cpy, size_t len);
int	check(char **result, char *s_cpy, size_t len);
char	**ft_split(char const *s, char c);


//libft
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2, size_t s2_len);

//push_swap
typedef struct s_node
{
	int				data;
	struct s_node	*pre;
	struct s_node	*next;
}t_node;

typedef struct s_stack
{
	int		size;
	t_node	*head;
	t_node	*tail;
}t_stack;
int	stack_init(int argc, char *argv[]);

#endif