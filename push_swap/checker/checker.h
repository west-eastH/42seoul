/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:52:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/17 18:11:18 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_node
{
	int				data;
	int				rank;
	struct s_node	*pre;
	struct s_node	*next;
}t_node;

typedef struct s_stack
{
	int		size;
	t_node	*head;
	t_node	*tail;
}t_stack;

typedef struct s_list
{
	int				fd;
	char			*st;
	struct s_list	*next;
}t_list;

char	*get_next_line(int fd);
char	*gnl_get_line(t_list **list, int fd);
int		is_line(const char *str);
ssize_t	read_file(t_list **list, int fd);

char	*gnl_strjoin(char *dest, char *src, ssize_t size);
char	*gnl_strndup(char *src, int n);
char	*gnl_substr(char *s, unsigned int start);
t_list	*gnl_getlist(t_list **list, int fd);
void	gnl_free(t_list **list, int fd);

int		push_back(t_stack *stack, int data);
int		push_front(t_stack *stack, int data);
int		pop_last(t_stack *stack);
int		pop_first(t_stack *stack);
void	push_stack(t_stack *dest, t_stack *src);

int		check_sign(char *str);
int		is_int(int argc, char *argv[]);
int		is_dup(int argc, char *argv[]);
int		init(t_stack *stack);
int		stack_init(int argc, char *argv[], t_stack *stack_a, t_stack *stack_b);

void	swap(t_stack *stack);
int		is_empty(t_stack *stack);
void	rotate(t_stack *stack);
void	rev_rotate(t_stack *stack);
void	set_rank(t_stack *stack);

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putendl_fd(char *s, int fd);

void	check_sort(t_stack *stack_a, t_stack *stack_b);
int		is_rotate(char *command, t_stack *stack_a, t_stack *stack_b);
int		is_swap_or_push(char *command, t_stack *stack_a, t_stack *stack_b);
int		check_command(char *command, t_stack *stack_a, t_stack *stack_b);
#endif