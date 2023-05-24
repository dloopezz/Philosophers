/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:33:36 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/05/24 18:11:53 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_data)
{
	t_philo *philo;

	philo = (t_philo *)philo_data;
	
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("philo %d has taken his left fork\n", philo->philo_id);
		
		pthread_mutex_lock(philo->right_fork);
		printf("philo %d has taken his right fork\n", philo->philo_id);

		printf("philo %d is eating\n", philo->philo_id);
		ft_usleep(philo->data->time_eat);
		
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		printf("philo %d is sleeping\n", philo->philo_id);
		ft_usleep(philo->data->time_sleep);
		
		printf("philo %d is thinking\n", philo->philo_id);
	}
	
	return (NULL);
}

int main (int argc, char **argv)
{
	t_data data;

	if (argc == 5 || argc == 6)
	{

		alloc_memory(&data);
		data_init(&data, argc, argv);
		philo_init(&data);
		create_forks(&data);
		int i = -1;
		while (++i < data.nb_philos)
		{
			pthread_create(&(data.tid[i]), NULL, &routine, &data.philos[i]);
			pthread_join(data.tid[i], NULL);
			//usleep
		}
	}
	else
		error_found("Error: invalid number of arguments");
	return 0;
}
