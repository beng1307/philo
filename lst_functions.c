#include "philo.h"

t_philo *ft_newphilo(int id)
{
	t_philo *new_philo;

    new_philo = ft_calloc(1, sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	if (pthread_mutex_init(&new_philo->fork, NULL) != 0)
		return (save_free((void **)new_philo), NULL);
    new_philo->id = id;
	new_philo->meal_counter = 0;
    new_philo->next = NULL;
	new_philo->prev = NULL;

    return (new_philo);
}

t_philo	*ft_last_philo(t_philo *philo)
{
	t_philo	*last_philo;

	if (!philo)
		return (NULL);
	last_philo = philo;
	while (last_philo->next)
		last_philo = last_philo->next;
	return (last_philo);
}

int    philo_add_back(t_philo **philo_list, t_philo *new_philo)
{
    t_philo  *last_philo;

	if (!philo_list || !new_philo)
		return (1);
	if (!*philo_list)
		*philo_list = new_philo;
	else
	{
    	last_philo = ft_last_philo(*philo_list);
    	last_philo->next = new_philo;
		new_philo->prev = last_philo;
	}

	return (0);
}