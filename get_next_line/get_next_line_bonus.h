/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:52:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/04/24 14:39:26 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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

size_t	ft_strlen(const char *s);
char	*ft_strdup(char *s1, size_t len);
char	*ft_strjoin(char *s1, char *s2, size_t s2_len);
t_list	*ft_find_fd(t_list *lst, int fd);
int		ft_backup(t_list **lst, int fd, char *buffer, int size);
int		is_line(char *backup);
char	*gnl_split(int fd, t_list **lst, int idx);
char	*no_line(int fd, t_list **lst, int size);
char	*get_next_line(int fd);
void	ft_free(t_list **lst, int fd);

#endif