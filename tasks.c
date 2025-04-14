#include "philo.h"

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->philo_dead_mutex);
	if (!*philo->philo_dead)
		safe_printf(philo, "is thinking");
	pthread_mutex_unlock(philo->philo_dead_mutex);
}

void	take_fork(t_philo *philo)
{
	if ((size_t)philo->id == *philo->number_of_philos)
	{
		pthread_mutex_lock(&philo->next->fork);
		pthread_mutex_lock(&philo->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
	}

	pthread_mutex_lock(philo->philo_dead_mutex);
	if (!*philo->philo_dead)
		safe_printf(philo, "has taken fork");
	pthread_mutex_unlock(philo->philo_dead_mutex);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->philo_dead_mutex);
	if (!*philo->philo_dead)
		safe_printf(philo, "is eating");
	pthread_mutex_unlock(philo->philo_dead_mutex);

	pthread_mutex_lock(philo->last_meal_time_mutex);
	philo->last_meal_time = timestamp_in_ms();
	pthread_mutex_unlock(philo->last_meal_time_mutex);

	usleep(*philo->time_to_eat * 1000);

	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->philo_dead_mutex);
	if (!*philo->philo_dead)
		safe_printf(philo, "is sleeping");
	pthread_mutex_unlock(philo->philo_dead_mutex);

	usleep(*philo->time_to_sleep * 1000);
}

void	died(t_philo *philo)
{
	pthread_mutex_lock(philo->philo_dead_mutex);
	safe_printf(philo, "died");
	*philo->philo_dead = true;
	pthread_mutex_unlock(philo->philo_dead_mutex);
}

bool	all_alive(t_data **data)
{
	t_philo	*philos;
	size_t	index;

	philos = (*data)->philo;
	index = 0;
	while (index < (*data)->number_of_philos)
	{
		pthread_mutex_lock(&(*data)->last_meal_time_mutex);
		if (timestamp_in_ms() - philos->last_meal_time > (*data)->time_to_die)
			return (pthread_mutex_unlock(&(*data)->last_meal_time_mutex), died(philos), false);
		pthread_mutex_unlock(&(*data)->last_meal_time_mutex);
		philos = philos->next;
		index++;
	}
	return (true);
}
