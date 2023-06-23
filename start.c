/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:00:23 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/06/22 15:51:44 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	alloc_memory(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->nb_philos);
	if (!data->tid)
		error_found("malloc error");
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		error_found("malloc error");
		
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		error_found("malloc error");
	data->lock = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->lock)
		error_found("malloc error");
	data->plock = malloc(sizeof(pthread_mutex_t));
	if (!data->plock)
		error_found("malloc error");
}

void	data_init(t_data *data, int argc, char **argv)
{
	data->nb_philos = ft_atoi_philo(argv[1]);		
	if (data->nb_philos >= 1 && data->nb_philos <= 200)
	{	
		data->time_die = ft_atoi_philo(argv[2]);
		data->time_sleep = ft_atoi_philo(argv[3]);
		data->time_eat = ft_atoi_philo(argv[4]);
		data->start = get_time();
		data->philo_died = 0;
		if (argc == 6)
			data->min_meals = ft_atoi_philo(argv[5]);
		else
			data->min_meals = 0;
	}
	else
		error_found("Error: no negative arguments allowed");
}

void	create_forks(t_data  *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->forks[i], NULL);
	data->philos[i].left_fork = &data->forks[i];
	data->philos[i].right_fork = &data->forks[data->nb_philos - 1];
	while (++i <= data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[i - 1];
	}
}

void	philo_init(t_data *data)
{
	int i;

	create_forks(data);
	i = -1;
	while (++i < data->nb_philos)
	{
		data->philos[i].data = data;
		data->philos[i].philo_id = i + 1;
		// data->philos[i].time_to_die = data->time_die; //no hace falta
		data->philos[i].status = 0;
		data->philos[i].is_eating = 0;
		data->philos[i].eat_cont = 0;
		data->philos[i].philo_died = data->philo_died;
		//mutexes
		pthread_mutex_init(&(data->lock[i]), NULL);
		data->philos[i].lock = &(data->lock[i]);
		pthread_mutex_init(&(data->plock[i]), NULL);
		data->philos[i].plock = data->plock;
	}
}
