#include "philo.h"

static void	*single_philos_life(void *philo)
{
	t_philo	*curr_philo;
	
	curr_philo = (t_philo *)philo;
	pthread_mutex_lock(&curr_philo->fork);
	safe_printf(curr_philo, "has taken fork");
	usleep(*curr_philo->time_to_die * 1000);
	safe_printf(curr_philo, "died");
	pthread_mutex_unlock(&curr_philo->fork);
	
	return (NULL);
}

void	single_philo(t_data **data)
{
	(*data)->starting_time = timestamp_in_ms();
	(*data)->dinning_started = true;
	pthread_create(&(*data)->philo->philosopher, NULL, single_philos_life, (void *)(*data)->philo);
}