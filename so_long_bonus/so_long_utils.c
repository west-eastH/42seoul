/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:43:09 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/18 17:42:14 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_map *map)
{
	t_map	*cur;
	t_map	*temp;

	cur = map;
	if (cur == NULL)
		return ;
	while (cur)
	{
		temp = cur->next;
		free(cur->line);
		cur->line = NULL;
		free(cur);
		cur = temp;
	}
}

void	free_copy_map(char	**map)
{
	int		i;
	char	*temp;

	i = 0;
	while (map[i])
	{
		temp = map[i];
		free(temp);
		temp = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

char	*move_print(t_param *par)
{
	char *result;
	char *move_cnt;

	move_cnt = move_to_char(par->move);
	result = ft_strjoin("move = ", move_cnt);
	free(move_cnt);
	return result;
}

char *move_to_char(int n)
{
	char *result;
	int len;
	int temp;

	len = 1;
	temp = n;
	while (temp > 9)
	{
		temp /= 10;
		len++;
	}
	result = (char *)malloc(len + 1);
	result[len] = 0;
	len--;
	while (n > 9)
	{
		result[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	result[len] = n % 10 + '0';
	return result;
}

