/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:11:47 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/16 20:01:48 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1, size_t len)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = (char *)malloc(len + 1);
	if (!temp)
		return (NULL);
	while (i < len)
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}

void	ft_free(t_list **lst, int fd)
{
	t_list	*cur;
	t_list	*pre;

	pre = *lst;
	cur = *lst;
	if ((*lst)->fd == fd)
	{
		*lst = cur->next;
		cur->next = NULL;
		free(cur);
		return ;
	}
	while (cur->next)
	{
		if (cur->fd == fd)
		{
			pre->next = cur->next;
			cur->next = NULL;
			free(cur);
			return ;
		}
		pre = cur;
		cur = cur->next;
	}
}

char	*ft_strjoin(char *s1, char *s2, size_t s2_len)
{
	char	*temp;
	size_t	s1_len;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1)
		return (ft_strdup(s2, s2_len));
	s1_len = ft_strlen(s1);
	temp = (char *)malloc(s1_len + s2_len + 1);
	if (!temp)
		return (NULL);
	while (s1[i++])
		temp[i - 1] = s1[i - 1];
	free(s1);
	j = 0;
	while (s2[j])
	{
		temp[i + j - 1] = s2[j];
		j++;
	}
	temp[i + j - 1] = 0;
	return (temp);
}

t_list	*ft_find_fd(t_list *lst, int fd)
{
	t_list	*temp;

	temp = lst;
	while (lst)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}







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
