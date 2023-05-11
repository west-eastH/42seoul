/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:31:19 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/02 20:15:46 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strjoin(char *dest, char *src, ssize_t size)
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
		return (NULL);
	}
	i = 0;
	while (dest[i++])
		temp[i - 1] = dest[i - 1];
	free(dest);
	while (src[j])
	{
		temp[i + j - 1] = src[j];
		j++;
	}
	temp[i + j - 1] = 0;
	return (temp);
}

ssize_t	read_file(t_list **list, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	t_list	*cur;
	ssize_t	size;

	cur = gnl_getlist(list, fd);
	if (cur == NULL)
		return (-1);
	while (is_line(cur->st) != 1)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size <= 0)
			break ;
		buffer[size] = 0;
		if (cur->st == NULL)
			cur->st = gnl_strndup(buffer, size);
		else
			cur->st = gnl_strjoin(cur->st, buffer, size);
		if (cur->st == NULL)
			return (-1);
		if (size < BUFFER_SIZE)
			break ;
	}
	return (size);
}

char	*gnl_get_line(t_list **list, int fd)
{
	size_t	i;
	t_list	*cur;
	char	*temp;
	char	*backup;

	cur = gnl_getlist(list, fd);
	i = 0;
	while (cur->st[i])
	{
		if (cur->st[i] == '\n')
			break ;
		i++;
	}
	temp = gnl_strndup(cur->st, i + 1);
	if (temp == NULL)
		return (NULL);
	backup = cur->st;
	cur->st = gnl_substr(cur->st, i + 1);
	free(backup);
	return (temp);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*result;
	char			*temp;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (0);
	if (read_file(&lst, fd) == -1)
	{
		if (gnl_getlist(&lst, fd)->st)
			free(gnl_getlist(&lst, fd)->st);
		gnl_free(&lst, fd);
		return (NULL);
	}
	result = gnl_getlist(&lst, fd)->st;
	if (result == NULL)
	{
		gnl_free(&lst, fd);
		return (NULL);
	}
	if (is_line(result) >= 0)
		return (gnl_get_line(&lst, fd));
	temp = gnl_strndup(result, -1);
	free(result);
	gnl_free(&lst, fd);
	return (temp);
}
