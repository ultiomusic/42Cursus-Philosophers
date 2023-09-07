/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seryilma <@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 03:14:09 by seryilma          #+#    #+#             */
/*   Updated: 2023/03/21 03:16:31 by seryilma         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_total_nbr_of_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->general_lock);
	philo->total_nbr_of_meals += 1;
	pthread_mutex_unlock(&philo->data->general_lock);
}

int	get_total_nbr_of_meals(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->general_lock);
	res = philo->total_nbr_of_meals;
	pthread_mutex_unlock(&philo->data->general_lock);
	return (res);
}

void	set_meals_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->general_lock);
	philo->total_nbr_of_meals -= 1;
	pthread_mutex_unlock(&philo->data->general_lock);
}

int	get_meals_left(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->general_lock);
	res = philo->meals_left;
	pthread_mutex_unlock(&philo->data->general_lock);
	return (res);
}

void	set_is_any_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->general_lock);
	philo->data->is_any_dead = i;
	pthread_mutex_unlock(&philo->data->general_lock);
}
