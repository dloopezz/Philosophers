/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:33:36 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/07/17 16:33:23 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_dinner(t_philo *philo)
{
	while (*(philo->end_flag) == FALSE)
	{
		pthread_mutex_unlock(philo->plock);
		pthread_mutex_lock(philo->right_fork);
		print_action("has taken a fork", philo);
		pthread_mutex_lock(philo->left_fork);
		print_action("has taken a fork", philo);
		pthread_mutex_lock(philo->lock);
		philo->last_meal = get_time() - philo->start;
		print_action("is eating", philo);
		if (philo->min_meals != -1)
			philo->eat_cont++;
		pthread_mutex_unlock(philo->lock);
		ft_usleep(philo->time_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_action("is sleeping", philo);
		ft_usleep(philo->time_sleep);
		print_action("is thinking", philo);
		pthread_mutex_lock(philo->plock);
	}
}

void	*routine(void *philo_data)
{
	t_philo	*philo;

	philo = philo_data;
	pthread_mutex_lock(philo->plock);
	pthread_mutex_unlock(philo->plock);
	if (philo->philo_id % 2 == 0)
		ft_usleep(200);
	pthread_mutex_lock(philo->plock);
	ft_dinner(philo);
	pthread_mutex_unlock(philo->plock);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		alloc_memory(&data, argv);
		if (data.nb_philos >= 1 && data.nb_philos <= 200)
		{
			pthread_mutex_lock(data.plock);
			philo_init(&data, argc, argv);
			pthread_mutex_unlock(data.plock);
			ft_death(&data);
			end_threads(&data);
			free_data(&data);
		}
		return (0);
	}
	else
		error_found("Error: invalid number of arguments");
	return (0);
}
