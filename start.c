/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:00:23 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/05/24 17:55:13 by dlopez-s         ###   ########.fr       */
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
	//alloc forks
}

void	data_init(t_data *data, int argc, char **argv)
{
	data->nb_philos = ft_atoi_philo(argv[1]);		
	if (data->nb_philos >= 1 && data->nb_philos <= 200)
		printf("Number of philos: %i\n", data->nb_philos); //cambiar para gestionar errores sin printf
	else
		error_found("Error: no negative arguments allowed");
	data->time_die = ft_atoi_philo(argv[2]);
	data->time_sleep = ft_atoi_philo(argv[3]);
	data->time_eat = ft_atoi_philo(argv[4]);
	if (argc == 6)
		data->min_meals = ft_atoi_philo(argv[5]);
	else
		data->min_meals = 0;
		
	data->is_dead = 0;
	data->thread_ended = 0;
	//init lock mutex
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

	i = -1;
	while (++i < data->nb_philos)
	{
		data->philos[i].data = data;
		data->philos[i].philo_id = i + 1;
		// data->philos[i].time_to_die = data->time_die; //no hace falta
		data->philos[i].status = 0;
		data->philos[i].is_eating = 0;
		data->philos[i].eat_cont = 0;
		//mutex
	}
}
