/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopezz <lopezz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:33:36 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/06/15 16:22:52 by lopezz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_data)
{
	t_philo *philo;

	philo = (t_philo *)philo_data;

	if (philo->philo_id % 2 == 0)
		ft_usleep(200);
	// pthread_mutex_lock(philo->lock);
	while (philo->data->philo_died == 0)
	{
		// pthread_mutex_unlock(philo->lock);
		pthread_mutex_lock(philo->left_fork);
		printf("%llums philo %d has taken his left fork\n", (get_time() - philo->data->start), philo->philo_id);

		pthread_mutex_lock(philo->right_fork);
		printf("%llums philo %d has taken his right fork\n", (get_time() - philo->data->start), philo->philo_id);

		printf("%llums philo %d is eating\n", (get_time() - philo->data->start), philo->philo_id);
		ft_usleep(philo->data->time_eat);

		
		pthread_mutex_lock(philo->lock);
		philo->last_meal = get_time() - philo->data->start;
		pthread_mutex_unlock(philo->lock);

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("%llums philo %d finished eating\n", (get_time() - philo->data->start), philo->philo_id);

		printf("%llums philo %d is sleeping\n", (get_time() - philo->data->start), philo->philo_id);
		ft_usleep(philo->data->time_sleep);

		printf("%llums philo %d is thinking\n", (get_time() - philo->data->start), philo->philo_id);
		
		printf("%llums philo %d no para\n", (get_time() - philo->data->start), philo->philo_id);
		// pthread_mutex_lock(philo->lock);
	}
	// pthread_mutex_unlock(philo->lock);
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
			if ((((get_time() - data->start) - data->philos[i].last_meal) > data->time_die))
			{
				// printf("ttdie: %llums\n", data->time_die);
				// printf("Last meal: %llums\n", data->philos[i].last_meal);
				
				printf("%llums philo %d died\n", (get_time() - data->start), data->philos[i].philo_id);
				pthread_mutex_lock(data->lock);
				data->philo_died = 1;
				pthread_mutex_unlock(data->lock);
				return ;
			}
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
		philo_init(&data);
		create_forks(&data);
		i = -1;
		while (++i < data.nb_philos)
			pthread_create(&(data.tid[i]), NULL, routine, &data.philos[i]);
		ft_death(&data);
		
		i = -1;
		while (++i < data.nb_philos)
			pthread_join(data.tid[i], NULL);
		// i = -1;
		// while (++i < data.nb_philos)
		// 	pthread_mutex_destroy(data.lock);
		
		return (0);
		
	}
	else
		error_found("Error: invalid number of arguments");
	return (0);
}
