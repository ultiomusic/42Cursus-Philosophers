#include "philo.h"

void	set_is_stopped(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->general_lock);
	philo->is_stopped = i;
	pthread_mutex_unlock(&philo->data->general_lock);
}

int	get_is_stopped(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->general_lock);
	res = philo->is_stopped;
	pthread_mutex_unlock(&philo->data->general_lock);
	return (res);
}

void	set_time_of_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->general_lock);
	philo->time_of_last_meal = ft_time();
	pthread_mutex_unlock(&philo->data->general_lock);
}

long	get_time_of_last_meal(t_philo *philo)
{
	long	res;

	pthread_mutex_lock(&philo->data->general_lock);
	res = philo->time_of_last_meal;
	pthread_mutex_unlock(&philo->data->general_lock);
	return (res);
}

int	get_is_any_dead(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->general_lock);
	res = philo->data->is_any_dead;
	pthread_mutex_unlock(&philo->data->general_lock);
	return (res);
}
