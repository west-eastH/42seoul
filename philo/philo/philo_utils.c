/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:55:20 by dongseo           #+#    #+#             */
/*   Updated: 2023/09/15 14:42:33 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (sign * res);
}

int	init(t_info *info, int argc, char *argv[])
{
	int	i;

	info->flag = 0;
	info->philo_num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]) * 1000;
	info->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 5)
		info->min_cnt = 0;
	else
		info->min_cnt = ft_atoi(argv[5]);
	if (info->philo_num <= 0 || info->time_to_die < 0 \
	|| info->time_to_eat < 0 || info->time_to_sleep < 0 || info->min_cnt < 0)
		return (1);
	info->lock = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (!info->lock)
		return (1);
	i = 0;
	while (i++ < info->philo_num)
		pthread_mutex_init(&(info->lock[i - 1]), NULL);
	pthread_mutex_init(&(info->print), NULL);
	pthread_mutex_init(&(info->eat_lock), NULL);
	pthread_mutex_init(&(info->flag_lock), NULL);
	gettimeofday(&info->start_time, NULL);
	return (0);
}

void	philo_printf(t_philo *philo, char *msg)
{
	struct timeval	now;
	int				diff;
	int				sec;
	int				ms;

	gettimeofday(&now, NULL);
	sec = (now.tv_sec - philo->info->start_time.tv_sec) * 1000000;
	ms = (now.tv_usec - philo->info->start_time.tv_usec);
	diff = (sec + ms) / 1000;
	pthread_mutex_lock(&(philo->info->print));
	pthread_mutex_lock(&(philo->info->flag_lock));
	if (!philo->info->flag)
		printf("%d %d %s", diff, philo->idx + 1, msg);
	pthread_mutex_unlock(&(philo->info->flag_lock));
	pthread_mutex_unlock(&(philo->info->print));
}

void	ft_usleep(int time)
{
	struct timeval	start;
	struct timeval	now;
	double			sec;
	double			ms;
	double			diff;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(10);
		gettimeofday(&now, NULL);
		sec = (now.tv_sec - start.tv_sec) * 1000000;
		ms = ((double)now.tv_usec - start.tv_usec);
		diff = sec + ms;
		if (diff > time)
			return ;
	}
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
