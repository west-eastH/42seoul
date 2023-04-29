/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:31:19 by dongseo           #+#    #+#             */
/*   Updated: 2023/04/29 18:12:42 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*gnl_getlist(t_list **list, int fd)
{
	t_list	*cur;
	t_list	*temp;

	cur = *list;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		if (!cur->next)
			break ;
		cur = cur->next;
	}
	temp = (t_list *)malloc(sizeof(t_list));
	if (!temp)
		return (NULL);
	temp->fd = fd;
	temp->st = NULL;
	temp->next = NULL;
	if (*list == NULL)
		*list = temp;
	else
		cur->next = temp;
	return temp;
}

int	is_line(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return -1;
	while (str[i])
	{
		if (str[i] == '\n')
			return 1;
		i++;
	}
	return -1;
}

char	*gnl_strndup(char *src, unsigned int n)
{
	char			*temp;
	unsigned int	i;

	i = 0;
	temp = (char *)malloc(n + 1);
	if (temp == NULL)
		return (NULL);
	while (i < n)
	{
		temp[i] = src[i];
		i++;
	}
	temp[i] = 0;
	return temp;
}

char	*gnl_strcat(char *dest, char *src, ssize_t size)
{
	char	*temp;
	ssize_t	i;
	ssize_t	j;

	j = 0;
	i = 0;
	while (dest[i])
		i++;
	temp = (char *)malloc(size + i + 1);
	if (temp == NULL)
	{
		free(dest);
		return NULL;
	}
	i = 0;
	while (dest[i++])
		temp[i - 1] = dest[i - 1];
	free(dest);
	while (src[j++])
		temp[i + j - 1] = src[j - 1];
	temp[i + j] = 0;
	return temp;
}

ssize_t	read_file(t_list *list, int fd)
{
	char	*buffer[BUFFER_SIZE + 1];
	t_list	*cur;
	ssize_t	size;

	cur = gnl_getlist(&list, fd);
	if (cur == NULL)
		return -1;
	while (is_line(cur->st) != 1)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size < 0)
			return -1;
		buffer[size] = 0;
		if (cur->st == NULL)
			cur->st = gnl_strndup(buffer, size);
		else
			cur->st = gnl_strcat(cur->st, buffer, size);
		if (cur->st == NULL)
			return -1;
		if (size < BUFFER_SIZE)
			break ;
	}
	return size;
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*result;
	ssize_t			read_check;

	if (fd < 0)
		return (0);
	read_check = read_file(lst, fd);
	if (read_check == -1)
		return NULL;
	// if (is_line(gnl_getlist(&lst, fd)->st))
	// 	get_line(&lst, fd);
}

#include <stdio.h>
#include <fcntl.h>
int main ()
{
	int f1,f2,f3,f4;
	f1 = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(f1));
	printf("%s", get_next_line(f1));
	printf("%s", get_next_line(f1));
	printf("%s", get_next_line(f1));
	
	return 0;
}