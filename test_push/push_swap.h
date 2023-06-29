/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:12:41 by dongseo           #+#    #+#             */
/*   Updated: 2023/06/28 21:59:29 by dongseo          ###   ########.fr       */
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
char	*ft_init(char *s_cpy, size_t len, size_t *word_cnt);
void	set_index(size_t index[]);
int	make_result(char **result, char *s_cpy, size_t len);
int	check(char **result, char *s_cpy, size_t len);
char	**ft_split(char const *s);


//libft
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2, size_t s2_len);
int	ft_atoi(const char *str);

//push_swap
typedef struct s_node
{
	int				data;
	int				ra_cnt;
	int				rb_cnt;
	int				flag;
	struct s_node	*pre;
	struct s_node	*next;
}t_node;

typedef struct s_stack
{
	int		size;
	t_node	*head;
	t_node	*tail;
}t_stack;

//init
int	stack_init(int argc, char *argv[], t_stack *stack_a, t_stack *stack_b);
int	check_sign(char *str);
int	is_int(char *str[]);
int	is_dup(char *str[]);
char	*join_argv(int argc, char *argv[]);

//stack_push_pop
int	push_back(t_stack *stack, int data);
int	push_front(t_stack *stack, int data);
int	pop_last(t_stack *stack);
int	pop_first(t_stack *stack);
int	init(t_stack *stack);

//push_swap_utils
void print_stack(t_stack *stack, t_stack *stack_b);
void	check_sort(t_stack *stack_a, t_stack *stack_b);

//manage_stack
void	swap(t_stack *stack, int flag);
void	rotate(t_stack *stack, int flag);
void	rev_rotate(t_stack *stack, int flag);
void	push_stack(t_stack *dest, t_stack *start, int flag);
int		get_top(t_stack *stack);

//push_swap
void	push_swap(t_stack *stack_a, t_stack *stack_b);
void	push_until_three(t_stack *stack_a, t_stack *stack_b);
void	sort_three(t_stack *stack);
void	sort_three_num(int a, int b, int c, t_stack *stack);


//push_b_to_a
void rotate_a(t_stack *stack_a, t_stack *stack_b, int cnt_a, int cnt_b);
void rotate_b(t_stack *stack_a, t_stack *stack_b, int cnt_a, int cnt_b);
void rotate_c(t_stack *stack_a, t_stack *stack_b, int cnt_a, int cnt_b);
void rotate_d(t_stack *stack_a, t_stack *stack_b, int cnt_a, int cnt_b);
#endif