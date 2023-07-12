/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:33:36 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/07/12 12:20:37 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_data)
{
	t_philo *philo;

	philo = philo_data;

	pthread_mutex_lock(philo->plock);
	pthread_mutex_unlock(philo->plock);

	if (philo->philo_id % 2 == 0)
 		ft_usleep(200);
		
	pthread_mutex_lock(philo->plock);
	while (philo->data->philo_died == 0)
	{
		pthread_mutex_unlock(philo->plock);

		pthread_mutex_lock(philo->left_fork);
		print_action("has taken his left fork", philo);

		pthread_mutex_lock(philo->right_fork);
		print_action("has taken his right fork", philo);

		print_action("is eating", philo);
		ft_usleep(philo->time_eat);

		pthread_mutex_lock(philo->lock);
		philo->last_meal = get_time() - philo->start;
		pthread_mutex_unlock(philo->lock);

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		print_action("is sleeping", philo);
		ft_usleep(philo->time_sleep);

		print_action("is thinking", philo);

		pthread_mutex_lock(philo->plock);
	}
	pthread_mutex_unlock(philo->plock);
	return (NULL);
}
 
void ft_death(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philos)
		{
			pthread_mutex_lock(data->philos[i].lock);
			if ((((get_time() - data->philos[i].start) - data->philos[i].last_meal) > data->philos[i].time_to_die))
			{
				print_action("died", &(data->philos[i]));
				pthread_mutex_lock(data->plock);
	            data->philo_died = 1;
				pthread_mutex_unlock(data->plock);
				return ;
			}
			pthread_mutex_unlock(data->philos[i].lock);
		}

		//while para count_meals
	}
}

int main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc == 5 || argc == 6)
	{
		alloc_memory(&data, argv);
		data_init(&data, argc, argv);
		pthread_mutex_lock(data.plock);
		philo_init(&data, argv);
		pthread_mutex_unlock(data.plock);
		ft_death(&data);
		
		i = -1;
		while (++i < data.nb_philos)
		{
			pthread_mutex_unlock(data.philos[i].lock);
			pthread_join(data.tid[i], NULL);  
		}
		i = -1;
		while (++i < data.nb_philos)
		{
		 	pthread_mutex_destroy(&(data.lock[i]));
		 	pthread_mutex_destroy(&(data.plock[i]));
		 	pthread_mutex_destroy(&(data.forks[i]));
		}
		// free(data.philos);
		// free(data.tid);
		// free(data.forks);
		// free(data.lock);
		// free(data.plock);
		return (0);
	}
	else
		error_found("Error: invalid number of arguments");
	return (0);
}
