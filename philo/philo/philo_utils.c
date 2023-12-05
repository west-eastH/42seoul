/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:55:20 by dongseo           #+#    #+#             */
/*   Updated: 2023/12/05 20:27:52 by dongseo          ###   ########.fr       */
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
	pthread_mutex_lock(&(philo->info->flag_lock));
	while (!philo->info->flag)
	{
		pthread_mutex_unlock(&(philo->info->flag_lock));
		usleep(100);
		gettimeofday(&now, NULL);
		diff = now.tv_sec * 1000000 + now.tv_usec - target;
		if (diff > time)
			return ;
		pthread_mutex_lock(&(philo->info->flag_lock));
	}
	pthread_mutex_unlock(&(philo->info->flag_lock));
}

void	take_up_fork(t_philo *philo, int num)
{
	pthread_mutex_lock(&(philo->info->flag_lock));
	while (!philo->info->flag)
	{
		pthread_mutex_unlock(&(philo->info->flag_lock));
		pthread_mutex_lock(&(philo->info->lock[philo->idx]));
		if (philo->info->fork[philo->idx] == 0)
		{
			philo->info->fork[philo->idx] = 1;
			pthread_mutex_lock(&(philo->info->lock[(philo->idx + 1) % num]));
			if (philo->info->fork[(philo->idx + 1) % num] == 0)
			{
				philo->info->fork[(philo->idx + 1) % num] = 1;
				philo_printf(philo, "has taken a fork\n");
				philo_printf(philo, "has taken a fork\n");
				return ;
			}
			pthread_mutex_unlock(&(philo->info->lock[philo->idx]));
		}
		philo->info->fork[philo->idx] = 0;
		pthread_mutex_unlock(&(philo->info->lock[philo->idx]));
		usleep(100);
		pthread_mutex_lock(&(philo->info->flag_lock));
	}
	pthread_mutex_unlock(&(philo->info->flag_lock));
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
