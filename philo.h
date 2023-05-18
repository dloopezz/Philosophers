/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:02:58 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/05/18 14:41:38 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>


typedef struct s_philo
{
	struct s_data	*data;
	// pthread_t       t1;
	// int             id;
	int             eat_cont;
	int             status;
	int             is_eating;
	uint64_t        time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
} 				t_philo;

typedef struct s_data
{
	t_philo         *philos;
	pthread_t       *tid;
	int             nb_philos;
	int             min_meals;
	int             is_dead;
	int             thread_ended;
	u_int64_t       time_die;
	u_int64_t       time_eat;
	u_int64_t       time_sleep;
	u_int64_t       thread_start;
	pthread_mutex_t *both_forks;
	pthread_mutex_t lock;
} 				t_data;

//Functions:
long long	ft_atoi_philo(const char *str);
int			error_found(char *str);

#endif