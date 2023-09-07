/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seryilma <@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 02:57:29 by seryilma          #+#    #+#             */
/*   Updated: 2023/03/21 03:04:36 by seryilma         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_init_args(t_data *data, int argc, char **argv)
{
	data->nbr_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->is_any_dead = 0;
	data->start_time = ft_time();
	if (argc == 5)
	{
		if (data->nbr_of_philos < 1)
			return (0);
		data->nbr_of_meals = -1;
	}
	else if (argc == 6)
	{
		data->nbr_of_meals = ft_atoi(argv[5]);
		if (data->nbr_of_meals < 1)
			return (0);
	}
	return (0);
}

void	ft_init_mutex(t_data *data)
{
	int				nbr_ph;
	pthread_mutex_t	*mutex;

	nbr_ph = data->nbr_of_philos;
	mutex = malloc(sizeof(pthread_mutex_t) * nbr_ph);
	while (nbr_ph--)
		pthread_mutex_init(&mutex[nbr_ph], NULL);
	pthread_mutex_init(&data->lock_for_print, NULL);
	pthread_mutex_init(&data->general_lock, NULL);
	data->forks = mutex;
}

void	ft_init_philosophers(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	while (i < data->nbr_of_philos)
	{
		philos[i].philo_id = i;
		philos[i].nbr_of_philos = data->nbr_of_philos;
		philos[i].total_nbr_of_meals = 0;
		philos[i].meals_left = data->nbr_of_meals;
		philos[i].time_to_eat = data->time_to_eat;
		philos[i].time_to_sleep = data->time_to_sleep;
		philos[i].time_to_die = data->time_to_die;
		philos[i].start_time = ft_time();
		philos[i].is_stopped = 0;
		philos[i].left_fork
			=&data->forks[philos[i].philo_id];
		philos[i].right_fork
			=&data->forks[(philos[i].philo_id + 1) % data->nbr_of_philos];
		philos[i].data = data;
		i++;
	}
	data->all_philos = philos;
}

void	ft_init_threads(t_data *data)
{
	int			i;
	pthread_t	*threads;
	pthread_t	death_controller;

	threads = malloc(sizeof(pthread_t) * data->nbr_of_philos);
	i = 0;
	while (i < data->nbr_of_philos)
	{
		pthread_create(&threads[i],
			NULL, ft_start_actions, (void *)&data->all_philos[i]);
		i += 2;
	}
	usleep(200);
	i = 1;
	while (i < data->nbr_of_philos)
	{
		pthread_create(&threads[i],
			NULL, ft_start_actions, (void *)&data->all_philos[i]);
		i += 2;
	}
	pthread_create(&death_controller,
		NULL, ft_monitor_threads, (void *)data->all_philos);
	pthread_join(death_controller, NULL);
	data->tids = threads;
}
