/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:37:31 by dongseo           #+#    #+#             */
/*   Updated: 2023/09/14 14:24:54 by dongseo          ###   ########.fr       */
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
	info->time_to_die = ft_atoi(argv[2]) * 1000;
	info->time_to_eat = ft_atoi(argv[3]) * 1000;
	info->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 5)
		info->min_cnt = 0;
	else
		info->min_cnt = ft_atoi(argv[5]);
	if (info->philo_num <= 0 || info->time_to_die < 0 ||
		info->time_to_eat < 0 || info->time_to_sleep < 0 || info->min_cnt < 0)
		return 1;
	info->lock = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (!info->lock)
		return 1;
	i = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_init(&(info->lock[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(info->print), NULL);
	gettimeofday(&info->start_time, NULL);
	return 0;
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
	printf("%dms philo %d %s", diff, philo->idx + 1, msg);
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

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->lock[philo->left]));
	philo_printf(philo, "has taken a fork\n");
	if (!pthread_mutex_lock(&(philo->info->lock[philo->right])))
	{
		philo_printf(philo, "has taken a fork\n");
		philo_printf(philo, "is eating\n");
		ft_usleep(philo->info->time_to_eat);
		philo->eat_cnt++;
		gettimeofday(&(philo->after_eat), NULL);
		pthread_mutex_unlock(&(philo->info->lock[philo->right]));
	}
	pthread_mutex_unlock(&(philo->info->lock[philo->left]));
}

void	*start(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->idx % 2 == 0)
		usleep(1000);
	while (!philo->info->flag)
	{
		eating(philo);
		if (philo->info->flag)
			break ;
		philo_printf(philo, "is sleeping\n");
		ft_usleep(philo->info->time_to_sleep);
		philo_printf(philo, "is thinking\n");
	}
	return NULL;
}

void	check_end(t_philo philo[])
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	if (!philo->info->min_cnt)
		return ;
	while (1)
	{
		j = 0;
		cnt = 0;
		while (j < philo[i].info->philo_num)
		{
			if (philo[j].eat_cnt >= philo[i].info->min_cnt)
				cnt++;
			j++;
		}
		if (cnt == philo[i].info->philo_num)
		{
			philo[i].info->flag = 1;
			return ;
		}
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

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo *philo;
	int		i;

	if (argc < 5 || argc > 6 || init(&info, argc, argv))
	{
		printf("error\n");
		return (0);
	}
	philo = (t_philo *)malloc(sizeof(t_philo) * info.philo_num);
	if (!philo)
		return (1);
	init_philo(&info, philo);
	i = 0;
	while (i < info.philo_num)
	{
		pthread_join(philo[i].pthread, NULL);
		i++;
	}
	return (0);
}
