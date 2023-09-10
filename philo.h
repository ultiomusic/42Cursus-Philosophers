#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "philo.h"

struct	s_data;

typedef struct s_philo
{
	int				philo_id;
	int				total_nbr_of_meals;
	int				meals_left;
	int				nbr_of_philos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				state;
	int				is_stopped;
	long			time_of_last_meal;
	time_t			start_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nbr_of_philos;
	int				philo_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_any_dead;
	int				nbr_of_meals;
	time_t			start_time;
	pthread_mutex_t	*forks;
	pthread_t		*tids;
	pthread_mutex_t	lock_for_print;
	pthread_mutex_t	general_lock;
	t_philo			*all_philos;
}	t_data;

// philo.c
int		ft_exit(char *msg);
int		ft_check_args(int argc, char **argv);
void	ft_usleep(int ms);

// utils.c
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *str, int fd);
int		ft_is_digit(char *str);
long	ft_time(void);

// init.c
int		ft_init_args(t_data *data, int argc, char **argv);
void	ft_init_mutex(t_data *data);
void	ft_init_philosophers(t_data *data);
void	ft_init_threads(t_data *data);

// setter_getter.c
void	set_total_nbr_of_meals(t_philo *philo);
int		get_total_nbr_of_meals(t_philo *philo);
void	set_meals_left(t_philo *philo);
int		get_meals_left(t_philo *philo);
void	set_is_any_dead(t_philo *philo, int i);

// setter_getter2.c
void	set_is_stopped(t_philo *philo, int i);
int		get_is_stopped(t_philo *philo);
void	set_time_of_last_meal(t_philo *philo);
long	get_time_of_last_meal(t_philo *philo);
int		get_is_any_dead(t_philo *philo);

// start_process.c
void	*ft_monitor_threads(void *args);
void	ft_philo_died(t_philo *philo);
int		ft_check_meals(t_philo *philos);
void	*ft_start_actions(void *args);

// actions.c
void	ft_taking_forks(t_philo *philo);
void	ft_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);
void	ft_thinking(t_philo *philo);

// end_process.c
void	ft_end_threads(t_data *data);
void	free_all(t_data *data);
void	unlock_and_destroy_mutex(t_data *data);

#endif
