/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:33:36 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/06/23 17:02:41 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_data)
{
	t_philo *philo;

	philo = (t_philo *)philo_data;

	// pthread_mutex_lock(philo->plock);
	// pthread_mutex_unlock(philo->plock);
	if (philo->philo_id % 2 == 0)
 		ft_usleep(200);
	pthread_mutex_lock(philo->plock);
	while (philo->data->philo_died == 0)
	{
		printf("se quedaid%d\n", philo->philo_id);
		pthread_mutex_unlock(philo->plock);

		pthread_mutex_lock(philo->left_fork);
		print_action("has taken his left fork", philo);

		pthread_mutex_lock(philo->right_fork);
		print_action("has taken his right fork", philo);

		print_action("is eating", philo);
		ft_usleep(philo->data->time_eat);


		pthread_mutex_lock(philo->lock);
		philo->last_meal = get_time() - philo->data->start;
		pthread_mutex_unlock(philo->lock);

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_action("finished eating", philo); //quitaaaaar

		print_action("is sleeping", philo);
		ft_usleep(philo->data->time_sleep);

		print_action("is thinking", philo);

		pthread_mutex_lock(philo->plock);
	}
	// pthread_mutex_unlock(philo->left_fork);
	// pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->lock);
	printf("id----%d\n", philo->philo_id);
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
			if ((((get_time() - data->start) - data->philos[i].last_meal) > data->time_die))
			{
				// printf("ttdie: %llums\n", data->time_die);
				// printf("Last meal: %llums\n", data->philos[i].last_meal);
				print_action("died", &(data->philos[i]));
				pthread_mutex_lock(data->plock);
	            data->philo_died = 1;
				// pthread_mutex_unlock(data->philos[i].left_fork); //AaAAaaAAa
				pthread_mutex_unlock(data->plock);
				return ;
			}
			pthread_mutex_unlock(data->philos[i].lock);
		}
	}
}

int main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc == 5 || argc == 6)
	{
		data_init(&data, argc, argv);
		alloc_memory(&data);
		pthread_mutex_lock(data.plock);
		philo_init(&data);
		pthread_mutex_unlock(data.plock);
		i = -1;
		
		pthread_mutex_lock(data.plock);
		while (++i < data.nb_philos)
			pthread_create(&(data.tid[i]), NULL, routine, &data.philos[i]);
		pthread_mutex_unlock(data.plock);
		ft_death(&data);
		pthread_mutex_unlock(data.plock);
		
		i = -1;
		while (++i < data.nb_philos)
			pthread_join(data.tid[i], NULL);
		i = -1;
		while (++i < data.nb_philos)
		{
		 	pthread_mutex_destroy(data.lock);
		 	pthread_mutex_destroy(data.plock);
		 	pthread_mutex_destroy(data.philos[i].lock);
		 	pthread_mutex_destroy(data.philos[i].plock);
		 	pthread_mutex_destroy(&(data.forks[i]));
		}
		
		return (0);
		
	}
	else
		error_found("Error: invalid number of arguments");
	return (0);
}
