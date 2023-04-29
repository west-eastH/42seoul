/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:52:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/04/29 16:01:33 by dongseo          ###   ########.fr       */
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

char	*get_next_line(int fd);
char	*get_line(t_list **list, int fd);
int		is_line(const char *str);
ssize_t	read_file(t_list *list, int fd);

char	*gnl_strcat(char *dest, char *src, ssize_t size);
char	*gnl_strndup(char *src, unsigned int n);
char	*gnl_substr(char *s, unsigned int start);
t_list	*gnl_getlist(t_list **list, int fd);
char	*gnl_free(t_list **list, int fd);

#endif