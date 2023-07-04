/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:52:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/04 15:43:50 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	int				fd;
	char			*st;
	struct s_list	*next;
}t_list;

size_t	gnl_ft_strlen(const char *s);
char	*gnl_ft_strdup(char *s1, size_t len);
char	*gnl_ft_strjoin(char *s1, char *s2, size_t s2_len);
t_list	*gnl_ft_find_fd(t_list *lst, int fd);
int		gnl_ft_backup(t_list **lst, int fd, char *buffer, int size);
int		gnl_is_line(char *backup);
char	*gnl_gnl_split(int fd, t_list **lst, int idx);
char	*gnl_no_line(int fd, t_list **lst, int size);
char	*gnl_get_next_line(int fd);
void	gnl_ft_free(t_list **lst, int fd);

#endif