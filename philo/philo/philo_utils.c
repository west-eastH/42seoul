/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:55:20 by dongseo           #+#    #+#             */
/*   Updated: 2023/12/20 10:44:12 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_diff(struct timeval time)
{
	struct timeval	now;
	int				diff;
	int				sec;
	int				ms;

	gettimeofday(&now, NULL);
	sec = (now.tv_sec - time.tv_sec) * 1000000;
	ms = (now.tv_usec - time.tv_usec);
	diff = (sec + ms) / 1000;
	return (diff);
}

void	philo_printf(t_philo *philo, char *msg)
{
	int				diff;

	pthread_mutex_lock(&(philo->info->flag_lock));
	if (!philo->info->flag)
	{
		diff = get_diff(philo->info->start_time);
		printf("%d %d %s", diff, philo->idx + 1, msg);
	}
	pthread_mutex_unlock(&(philo->info->flag_lock));
}

void	ft_usleep(long long time, t_philo *philo)
{
	struct timeval	start;
	struct timeval	now;
	long long		diff;
	long long		target;

	gettimeofday(&start, NULL);
	target = start.tv_sec * 1000000 + start.tv_usec;
	while (!check_flag(philo))
	{
		usleep(100);
		gettimeofday(&now, NULL);
		diff = now.tv_sec * 1000000 + now.tv_usec - target;
		if (diff > time)
			return ;
	}
}

int	check_flag(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->flag_lock));
	if (philo->info->flag == 0)
	{
		pthread_mutex_unlock(&(philo->info->flag_lock));
		return (0);
	}
	pthread_mutex_unlock(&(philo->info->flag_lock));
	return (1);
}

int	free_all(t_info *info, t_philo *philo, int exit_num)
{
	if (philo)
		free(philo);
	if (info->after_lock)
		free(info->after_lock);
	if (info->lock)
		free(info->lock);
	if (info->fork)
		free(info->fork);
	if (info->cnt_lock)
		free(info->cnt_lock);
	return (exit_num);
}
