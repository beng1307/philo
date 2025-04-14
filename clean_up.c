#include "philo.h"

void	save_free(void **to_free)
{
	if (to_free && *to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
}

void    free_philos(t_philo **philo)
{
    t_philo *philo_to_free;

    if (!philo || !*philo)
        return ;
    while (*philo)
    {
        philo_to_free = *philo;
        *philo = (*philo)->next;

        pthread_mutex_destroy(&philo_to_free->fork);
        save_free((void **)philo_to_free);
    }
}

void    join_threads(t_data **data)
{
    size_t  index;

    index = 0;
	while (index < (*data)->number_of_philos)
	{
		pthread_join((*data)->philo->philosopher, NULL);
		(*data)->philo = (*data)->philo->next;
		index++;
	}
}

void    destroy_data(t_data **data)
{
    if ((*data)->print_mutex_exists)
        pthread_mutex_destroy(&(*data)->print_mutex);
    if ((*data)->last_meal_time_mutex_exists)
        pthread_mutex_destroy(&(*data)->last_meal_time_mutex);
    if ((*data)->philo_dead_mutex_exists)
        pthread_mutex_destroy(&(*data)->philo_dead_mutex);

    save_free((void **)data);
}

void	clean_up(t_data **data)
{
    if ((*data)->dinning_started)
        join_threads(data);
    free_philos(&(*data)->philo);
    destroy_data(data);
}