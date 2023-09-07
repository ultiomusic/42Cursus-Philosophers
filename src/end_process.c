#include "../includes/philo.h"

void	ft_end_threads(t_data *data)
{
	int	nbr_ph;

	nbr_ph = data->nbr_of_philos;
	if (nbr_ph == 1)
	{
		pthread_mutex_unlock(&data->forks[0]);
	}
	while (nbr_ph)
	{
		nbr_ph--;
		pthread_join(data->tids[nbr_ph], NULL);
	}
}

void	free_all(t_data *data)
{
	free(data->tids);
	free(data->all_philos);
	free(data->forks);
}

void	unlock_and_destroy_mutex(t_data *data)
{
	int	nbr_ph;

	nbr_ph = data->nbr_of_philos;
	while (nbr_ph--)
	{
		pthread_mutex_unlock(&data->forks[nbr_ph]);
		pthread_mutex_destroy(&data->forks[nbr_ph]);
	}
	pthread_mutex_unlock(&data->lock_for_print);
	pthread_mutex_destroy(&data->lock_for_print);
	pthread_mutex_unlock(&data->general_lock);
	pthread_mutex_destroy(&data->general_lock);
}
