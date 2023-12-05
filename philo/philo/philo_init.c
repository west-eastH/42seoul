/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:25:53 by dongseo           #+#    #+#             */
/*   Updated: 2023/12/05 20:00:54 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init(t_info *info)
{
	int	i;

	i = 0;
	while (i++ < info->philo_num)
	{
		pthread_mutex_init(&(info->lock[i - 1]), NULL);
		pthread_mutex_init(&(info->after_lock[i - 1]), NULL);
		pthread_mutex_init(&(info->cnt_lock[i - 1]), NULL);
	}
	pthread_mutex_init(&(info->flag_lock), NULL);
}

int	mutex_malloc(t_info *info)
{
	int	i;

	info->fork = malloc(sizeof(int) * info->philo_num);
	if (!info->fork)
		return (1);
	i = 0;
	while (i++ < info->philo_num)
		info->fork[i] = 0;
	info->lock = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (!info->lock)
		return (1);
	info->after_lock = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (!info->after_lock)
		return (1);
	info->cnt_lock = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (!info->cnt_lock)
		return (1);
	return (0);
}

int	init(t_info *info, int argc, char *argv[])
{
	info->flag = 0;
	info->philo_num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		info->min_cnt = -1;
	else
	{
		info->min_cnt = ft_atoi(argv[5]);
		if (info->min_cnt < 0)
			return (1);
		else if (info->min_cnt == 0)
			return (2);
	}
	if (info->philo_num <= 0 || info->time_to_die < 0
		|| info->time_to_eat < 0 || info->time_to_sleep < 0)
		return (1);
	if (mutex_malloc(info))
		return (1);
	mutex_init(info);
	gettimeofday(&info->start_time, NULL);
	return (0);
}

void	init_philo(t_info *info, t_philo philo[])
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		philo[i].idx = i;
		philo[i].eat_cnt = 0;
		philo[i].info = info;
		gettimeofday(&(philo[i].after_eat), NULL);
		pthread_create(&(philo[i].pthread), NULL, start, &(philo[i]));
		i++;
	}
	check_end(philo);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	res;
	int			sign;

	sign = 1;
	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		if (res > 2147483647)
			return (-1);
		i++;
	}
	return (sign * res);
}
