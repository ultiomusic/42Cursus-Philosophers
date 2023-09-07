/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seryilma <@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 03:05:03 by seryilma          #+#    #+#             */
/*   Updated: 2023/03/21 04:58:59 by seryilma         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_taking_left_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (get_is_any_dead(philo) || get_is_stopped(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(&philo->data->lock_for_print);
	if (get_is_any_dead(philo) || get_is_stopped(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->data->lock_for_print);
		return ;
	}
	printf("%ld %d has taken a fork\n",
		ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->lock_for_print);
}

void	ft_taking_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (get_is_any_dead(philo) || get_is_stopped(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(&philo->data->lock_for_print);
	if (get_is_any_dead(philo) || get_is_stopped(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->data->lock_for_print);
		return ;
	}
	printf("%ld %d has taken a fork\n",
		ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->lock_for_print);
	ft_taking_left_forks(philo);
}

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_for_print);
	if (get_is_any_dead(philo) || get_is_stopped(philo))
	{
		pthread_mutex_unlock(&philo->data->lock_for_print);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	printf("%ld %d is eating\n",
		ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->lock_for_print);
	set_total_nbr_of_meals(philo);
	set_time_of_last_meal(philo);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_for_print);
	if (get_is_any_dead(philo) || get_is_stopped(philo))
	{
		pthread_mutex_unlock(&philo->data->lock_for_print);
		return ;
	}
	printf("%ld %d is sleeping\n",
		ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->lock_for_print);
	ft_usleep(philo->time_to_sleep);
}

void	ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_for_print);
	if (get_is_any_dead(philo) || get_is_stopped(philo))
	{
		pthread_mutex_unlock(&philo->data->lock_for_print);
		return ;
	}
	printf("%ld %d is thinking\n",
		ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->lock_for_print);
}
