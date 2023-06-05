/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopezz <lopezz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:02:58 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/06/05 18:26:19 by lopezz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
#include <sys/time.h>

#define TRUE 0
#define FALSE 1

typedef struct s_philo
{
	struct s_data	*data;
	// pthread_t       t1;
	int             philo_id;
	int             eat_cont;
	int             status;
	int             is_eating;
	long long		last_meal;
	uint64_t        time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
} 				t_philo;

typedef struct s_data
{
	t_philo         *philos;
	pthread_t       *tid;
	int             nb_philos;
	int             min_meals;
	int             philo_died;
	// int             thread_ended;
	uint64_t		start;
	u_int64_t       time_die;
	u_int64_t       time_eat;
	u_int64_t       time_sleep;
	pthread_mutex_t *forks;
	pthread_mutex_t lock;
} 				t_data;

//Utils
long long	ft_atoi_philo(const char *str);
int			error_found(char *str);
uint64_t	get_time(void);
int 		ft_usleep(unsigned int time);

//Initialization
void	alloc_memory(t_data *data);
void	data_init(t_data *data, int argc, char **argv);
void	philo_init(t_data *data);
void	create_forks(t_data  *data);

#endif