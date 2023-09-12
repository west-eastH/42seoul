/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:12:23 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/12 15:09:43 by dongseo          ###   ########.fr       */
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
	int				fork;
	int				die;
	int				eat;
	int				sleep;
	int				min_cnt;
	int				flag;
	struct timeval	start_time;
}	t_info;

typedef struct s_philo
{
	int				idx;
	struct timeval	life;
	int				left;
	int				right;
	struct s_philo	prev;
	struct s_philo	next;
	t_info			*info;
}	t_philo;
#endif
