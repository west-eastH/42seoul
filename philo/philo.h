/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:12:23 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/14 14:04:23 by dongseo          ###   ########.fr       */
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
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_cnt;
	int				flag;
	pthread_mutex_t	*lock;
	pthread_mutex_t	print;
	struct timeval	start_time;
}	t_info;

typedef struct s_philo
{
	int				idx;
	struct timeval	after_eat;
	int				eat_cnt;
	int				left;
	int				right;
	pthread_t		pthread;
	t_info			*info;
}	t_philo;
#endif
