/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:31:15 by dongseo           #+#    #+#             */
/*   Updated: 2023/12/07 16:47:36 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_fork(t_philo *philo, int lr)
{
	t_info	*info;
	int		idx;

	info = philo->info;
	if (lr == 0)
		idx = philo->idx;
	else
		idx = (philo->idx + 1) % info->philo_num;
	pthread_mutex_lock(&(info->lock[idx]));
	if (info->fork[idx] == 0)
	{
		info->fork[idx] = 1;
		pthread_mutex_unlock(&(info->lock[idx]));
		return (1);
	}
	pthread_mutex_unlock(&(info->lock[idx]));
	return (0);
}

void	take_up_fork(t_philo *philo)
{
	while (!check_flag(philo))
	{
		if (check_fork(philo, 0))
		{
			philo_printf(philo, "has taken a fork\n");
			while (!check_flag(philo))
			{
				if (check_fork(philo, 1))
				{
					philo_printf(philo, "has taken a fork\n");
					return ;
				}
				usleep(100);
			}
		}
		usleep(100);
	}
}

void	eating(t_philo *philo)
{
	int	num;

	if (philo->info->philo_num > 1)
	{
		num = philo->info->philo_num;
		take_up_fork(philo);
		philo_printf(philo, "is eating\n");
		pthread_mutex_lock(&(philo->info->after_lock[philo->idx]));
		gettimeofday(&(philo->after_eat), NULL);
		pthread_mutex_unlock(&(philo->info->after_lock[philo->idx]));
		ft_usleep(philo->info->time_to_eat * 1000, philo);
		pthread_mutex_lock(&(philo->info->cnt_lock[philo->idx]));
		philo->eat_cnt++;
		pthread_mutex_unlock(&(philo->info->cnt_lock[philo->idx]));
		unlock_fork(philo, 1);
		unlock_fork(philo, 0);
		return ;
	}
	philo_printf(philo, "has taken a fork\n");
	ft_usleep(philo->info->time_to_die * 1500, philo);
}

void	unlock_fork(t_philo *philo, int lr)
{
	t_info	*info;
	int		idx;

	info = philo->info;
	if (lr == 0)
		idx = philo->idx;
	else
		idx = (philo->idx + 1) % info->philo_num;
	pthread_mutex_lock(&(info->lock[idx]));
	info->fork[idx] = 0;
	pthread_mutex_unlock(&(info->lock[idx]));
}
