/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:51:27 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/02 18:59:54 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	gnl_free(t_list **lst, int fd)
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

char	*gnl_substr(char *s, unsigned int start)
{
	char	*temp;
	size_t	i;

	i = 0;
	while (s[i + start])
		i++;
	if (i == 0)
		return (NULL);
	temp = (char *)malloc(i + 1);
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (s[i + start])
	{
		temp[i] = s[i + start];
		i++;
	}
	temp[i] = 0;
	return (temp);
}

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
	return (temp);
}

int	is_line(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (-1);
}

char	*gnl_strndup(char *src, int n)
{
	char	*temp;
	int		i;

	i = 0;
	if (n == 0)
		return (NULL);
	if (n != -1)
		temp = (char *)malloc(n + 1);
	else
	{
		while (src[i])
			i++;
		temp = (char *)malloc(i + 1);
		n = i;
	}
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		temp[i] = src[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}
