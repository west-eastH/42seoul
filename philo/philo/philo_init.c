/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:25:53 by dongseo           #+#    #+#             */
/*   Updated: 2023/11/30 09:47:48 by dongseo          ###   ########.fr       */
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
	}
	pthread_mutex_init(&(info->flag_lock), NULL);
}

int	init(t_info *info, int argc, char *argv[])
{
	info->flag = 0;
	info->philo_num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]) * 1000;
	info->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 5)
		info->min_cnt = 0;
	else
		info->min_cnt = ft_atoi(argv[5]);
	if (info->philo_num <= 0 || info->time_to_die < 0
		|| info->time_to_eat < 0 || info->time_to_sleep < 0
		|| info->min_cnt < 0)
		return (1);
	info->lock = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (!info->lock)
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
		philo[i].left = i;
		philo[i].right = (i + 1) % info->philo_num;
		philo[i].info = info;
		gettimeofday(&(philo[i].after_eat), NULL);
		pthread_create(&(philo[i].pthread), NULL, start, &(philo[i]));
		i++;
	}
	check_end(philo);
}
