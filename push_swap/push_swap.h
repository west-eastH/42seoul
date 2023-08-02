/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:12:41 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/02 21:43:46 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

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

char				*ft_init(char *s_cpy, size_t len, size_t *word_cnt);
void				set_index(size_t index[]);
int					make_result(char **result, char *s_cpy, size_t len);
int					check(char **result, char *s_cpy, size_t len);
char				**ft_split(char const *s);

size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char *s1, char *s2, size_t s2_len);
long long			ft_atoi(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

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

int					stack_init(int argc, char *argv[],
						t_stack *stack_a, t_stack *stack_b);
int					check_sign(char *str);
int					is_int(char *str[]);
int					is_dup(char *str[]);
char				*join_argv(int argc, char *argv[]);

int					push_back(t_stack *stack, int data);
int					push_front(t_stack *stack, int data);
int					pop_last(t_stack *stack);
int					pop_first(t_stack *stack);
int					init(t_stack *stack);

void				swap(t_stack *stack, int flag);
void				rotate(t_stack *stack, int flag);
void				rev_rotate(t_stack *stack, int flag);
void				push_stack(t_stack *dest, t_stack *start, int flag);
int					get_top(t_stack *stack);

void				push_swap(t_stack *stack_a, t_stack *stack_b);
void				push_until_three(t_stack *stack_a, t_stack *stack_b);
void				sort_three(t_stack *stack);
void				sort_three_num(int a, int b, int c, t_stack *stack);

void				rotate_a(t_stack *stack_a, t_stack *stack_b,
						int cnt_a, int cnt_b);
void				rotate_b(t_stack *stack_a, t_stack *stack_b,
						int cnt_a, int cnt_b);
void				rotate_c(t_stack *stack_a, t_stack *stack_b,
						int cnt_a, int cnt_b);
void				rotate_d(t_stack *stack_a, t_stack *stack_b,
						int cnt_a, int cnt_b);
void				push_b_to_a(t_stack *stack_a,
						t_stack *stack_b, t_node *cur);

int					set_mm_ra(t_stack *stack_a);
void				set_ra_cnt(t_stack *stack_a, t_stack *stack_b);
void				set_rb_cnt(t_stack *stack_b);
int					set_min_cnt(int *min_cnt, t_node *cur, int flag, int size);
int					find_min(t_stack *stack_a, t_stack *stack_b);

void				check_ra(t_stack *stack_a);
int					is_sort(t_stack *stack);
int					set_pivot(t_stack *stack_a, int flag);
void				push_sort(t_stack *stack_a, t_stack *stack_b,
						int p1, int p2);
void				push_a_to_b(t_stack *stack_a, t_stack *stack_b);

void				ft_free(char **str);
char				**ft_join_split(int argc, char *argv[]);
#endif