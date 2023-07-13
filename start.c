/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopezz <lopezz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:00:23 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/07/12 16:16:14 by lopezz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	alloc_memory(t_data *data, char **argv)
{
	data->nb_philos = ft_atoi_philo(argv[1]);		
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
	data->plock = malloc(sizeof(pthread_mutex_t) * 1);
	if (!data->plock)
		error_found("malloc error");
	data->start = get_time();
	data->philo_died = 0;
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

void	philo_init(t_data *data, int argc, char **argv)
{
	int i;

	i = -1;
	create_forks(data);
	while (++i < data->nb_philos)
	{
		pthread_mutex_init(&(data->lock[i]), NULL);
		data->philos[i].lock = &(data->lock[i]);
		pthread_mutex_init(&(data->plock[i]), NULL);
		data->philos[i].plock = data->plock;

		data->philos[i].data = data;
		data->philos[i].philo_id = i + 1;
		data->philos[i].start = data->start;
		data->philos[i].philo_died = data->philo_died;
		data->philos[i].time_to_die = ft_atoi_philo(argv[2]);
		data->philos[i].time_sleep = ft_atoi_philo(argv[3]);
		data->philos[i].time_eat = ft_atoi_philo(argv[4]);
		// count_meals
		data->philos[i].last_meal = 0;
		data->philos[i].eat_cont = 0;
		if (argc == 6)
			data->philos[i].min_meals = ft_atoi_philo(argv[5]);
		else if (argc == 5)
			data->philos[i].min_meals = -1;

		pthread_create(&(data->tid[i]), NULL, routine, &data->philos[i]);
	}
}
