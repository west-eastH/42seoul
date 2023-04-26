/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:11:47 by dongseo           #+#    #+#             */
/*   Updated: 2023/04/24 14:39:33 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_backup(t_list **lst, int fd, char *buffer, int size)
{
	t_list	*temp;
	t_list	*cur;

	cur = ft_find_fd(*lst, fd);
	if (cur != NULL)
	{
		cur->st = ft_strjoin(cur->st, buffer, size);
		return (0);
	}
	cur = (t_list *)malloc(sizeof(t_list));
	if (!cur)
		return (1);
	cur->fd = fd;
	cur->st = ft_strjoin(NULL, buffer, size);
	cur->next = NULL;
	if (!*lst)
	{
		*lst = cur;
		return (0);
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = cur;
	return (0);
}

int	is_line(char *backup)
{
	size_t	i;

	i = 0;
	if (backup == NULL)
		return (-1);
	while (backup[i])
	{
		if (backup[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*gnl_split(int fd, t_list **lst, int idx)
{
	t_list	*cur;
	size_t	len;
	char	*result;
	char	*temp;

	cur = ft_find_fd(*lst, fd);
	result = ft_strdup(cur->st, idx + 1);
	if (!result)
		return (NULL);
	if (cur->st[idx + 1] != '\0')
	{
		len = ft_strlen(cur->st + idx + 1);
		temp = ft_strdup(cur->st + idx + 1, len);
		if (!temp)
		{
			free(cur->st);
			ft_free(lst, fd);
			return (NULL);
		}
	}
	else
		temp = NULL;
	free(cur->st);
	cur->st = temp;
	return (result);
}

char	*no_line(int fd, t_list **lst, int size)
{
	t_list	*cur;
	int		idx;
	char	*temp;

	if (size < 0)
		return (NULL);
	cur = ft_find_fd(*lst, fd);
	if (!cur)
		return (NULL);
	idx = is_line(cur->st);
	if (0 <= idx)
		return (gnl_split(fd, lst, idx));
	if (!cur->st)
	{
		ft_free(lst, fd);
		return (NULL);
	}
	temp = ft_strdup(cur->st, ft_strlen(cur->st));
	free(cur->st);
	cur->st = NULL;
	ft_free(lst, fd);
	return (temp);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			buffer[BUFFER_SIZE + 1];
	int				size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	size = read(fd, buffer, BUFFER_SIZE);
	while (0 < size)
	{
		buffer[size] = 0;
		if (ft_backup(&lst, fd, buffer, size))
			return (NULL);
		if (is_line(ft_find_fd(lst, fd)->st) >= 0)
			return (gnl_split(fd, &lst, is_line(ft_find_fd(lst, fd)->st)));
		size = read(fd, buffer, BUFFER_SIZE);
	}
	if (size < 0 && ft_find_fd(lst, fd))
	{
		free(ft_find_fd(lst, fd)->st);
		ft_free(&lst, fd);
		return (NULL);
	}
	return (no_line(fd, &lst, size));
}
