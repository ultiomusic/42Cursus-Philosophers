#include "philo.h"

void	ft_usleep(int ms)
{
	long	time;

	time = ft_time();
	usleep(ms * 500);
	while (ft_time() - time < ms)
		usleep(100);
}

int	ft_exit(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	return (1);
}

int	ft_check_args(int argc, char **argv)
{
	size_t	i;

	if (argc < 5 || argc > 6)
		return (ft_exit("Please enter 4 or 5 arguments!\n"));
	i = 1;
	while (argv[i])
	{
		if (!ft_is_digit(argv[i]) || (!ft_atoi(argv[i]))
			|| (ft_atoi(argv[i]) > __INT_MAX__))
			return (ft_exit("Invalid argument\n"));
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_check_args(argc, argv))
		return (EXIT_FAILURE);
	if (ft_init_args(&data, argc, argv))
		return (EXIT_FAILURE);
	ft_init_mutex(&data);
	ft_init_philosophers(&data);
	ft_init_threads(&data);
	ft_end_threads(&data);
	unlock_and_destroy_mutex(&data);
	free_all(&data);
	return (EXIT_SUCCESS);
}
