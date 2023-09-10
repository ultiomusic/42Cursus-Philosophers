#include "philo.h"

void	ft_philo_died(t_philo *philo)
{
	int	i;

	set_is_any_dead(philo, 1);
	i = 0;
	while (i < philo->nbr_of_philos)
	{
		set_is_stopped(&philo->data->all_philos[i], 1);
		i++;
	}
	pthread_mutex_lock(&philo->data->lock_for_print);
	printf("%ld %d died\n", ft_time() - philo->start_time,
		philo->philo_id + 1);
}

int	ft_check_meals(t_philo *philos)
{
	int	flag_enough;
	int	i;

	if (get_total_nbr_of_meals(philos) != -1 && get_meals_left(philos) > 0)
	{
		flag_enough = 1;
		i = -1;
		while (++i < philos->nbr_of_philos)
			if (get_total_nbr_of_meals(&philos[i]) < get_meals_left(&philos[i]))
				flag_enough = 0;
		if (flag_enough == 1)
		{
			i = -1;
			while (++i < philos->nbr_of_philos)
				set_is_stopped(&philos[i], 1);
			return (1);
		}
	}
	return (0);
}

void	*ft_monitor_threads(void *args)
{
	t_philo	*philos;
	time_t	time_now;
	int		i;

	philos = (t_philo *)args;
	i = 0;
	while (!get_is_any_dead(&philos[0]))
	{
		i = -1;
		while (++i < philos->nbr_of_philos)
		{
			time_now = ft_time();
			if (time_now - get_time_of_last_meal(&philos[i])
				> philos[i].time_to_die)
			{
				ft_philo_died(&philos[i]);
				pthread_mutex_unlock(&philos[i].data->lock_for_print);
				return (NULL);
			}
		}
		if (ft_check_meals(philos) || get_is_stopped(philos))
			return (NULL);
	}
	return (NULL);
}

void	*ft_start_actions(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	set_time_of_last_meal(philo);
	philo->start_time = ft_time();
	while (!get_is_any_dead(philo))
	{
		if (get_is_any_dead(philo) || get_is_stopped(philo))
			return (NULL);
		ft_taking_forks(philo);
		if (get_is_any_dead(philo) || get_is_stopped(philo))
			return (NULL);
		ft_eating(philo);
		if (get_is_any_dead(philo) || get_is_stopped(philo))
			return (NULL);
		ft_sleeping(philo);
		if (get_is_any_dead(philo) || get_is_stopped(philo))
			return (NULL);
		ft_thinking(philo);
		if (get_is_any_dead(philo) || get_is_stopped(philo))
			return (NULL);
	}
	return (NULL);
}
