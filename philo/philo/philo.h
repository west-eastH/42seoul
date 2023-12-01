/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:12:23 by yusekim           #+#    #+#             */
/*   Updated: 2023/12/01 12:49:05 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_info
{
	int				philo_num;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				min_cnt;
	int				flag;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*after_lock;
	pthread_mutex_t	*cnt_lock;
	pthread_mutex_t	flag_lock;
	struct timeval	start_time;
}	t_info;

typedef struct s_philo
{
	int				idx;
	struct timeval	after_eat;
	int				eat_cnt;
	pthread_t		pthread;
	t_info			*info;
}	t_philo;

void	mutex_init(t_info *info);
int		init(t_info *info, int argc, char *argv[]);
void	init_philo(t_info *info, t_philo philo[]);
int		ft_atoi(const char *str);
void	philo_printf(t_philo *philo, char *msg);
void	ft_usleep(int time, t_philo *philo);
void	eating(t_philo *philo);
void	*start(void *data);
int		is_died(t_philo *philo);
void	check_end(t_philo philo[]);
int		get_diff(struct timeval time);
#endif
