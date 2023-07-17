/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:02:58 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/07/17 16:20:01 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

# define TRUE 0
# define FALSE 1

typedef struct s_philo
{
	struct s_data	*data;
	int				philo_id;
	int				eat_cont;
	int				min_meals;
	int				is_fat;
	int				*end_flag;
	long long		last_meal;
	uint64_t		start;
	u_int64_t		time_eat;
	u_int64_t		time_sleep;
	uint64_t		time_to_die;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*plock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}				t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_t		*tid;
	int				nb_fat;
	int				end_flag;
	int				nb_philos;
	uint64_t		start;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*plock;
	pthread_mutex_t	*forks;
}				t_data;

//Utils
long long	ft_atoi_philo(const char *str);
int			error_found(char *str);
uint64_t	get_time(void);
int			ft_usleep(unsigned int time);
void		print_action(char *action, t_philo *philo);

//Init Data
void		alloc_memory(t_data *data, char **argv);
void		philo_init(t_data *data, int argc, char **argv);
void		mutex_init(t_data *data, int i);

//Philo
void		*routine(void *philo_data);
void		ft_dinner(t_philo *philo);
void		ft_death(t_data *data);
int			check_meals(t_data *data, int i);
int			check_death_time(t_data *data, int i);

//End Program
void		end_threads(t_data *data);
void		free_data(t_data *data);

#endif