/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:33:47 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/17 17:25:59 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	save_free(void **to_free)
{
	if (to_free && *to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
}

void	join_threads(t_data **data)
{
	size_t	index;

	index = 0;
	while (index < (*data)->number_of_philos)
	{
		pthread_join((*data)->philo->philosopher, NULL);
		(*data)->philo = (*data)->philo->next;
		index++;
	}
}

void	free_philos(t_philo **philo)
{
	t_philo	*philo_to_free;
	size_t	index;
	size_t	number_of_philos;

	if (!philo || !*philo)
		return ;
	index = 0;
	number_of_philos = *(*philo)->number_of_philos;
	while (index < number_of_philos)
	{
		philo_to_free = (*philo)->next;
		pthread_mutex_destroy(&(*philo)->fork);
		save_free((void **)philo);
		*philo = philo_to_free;
		index++;
	}
}

void	destroy_data(t_data **data)
{
	if ((*data)->print_mutex_exists)
		pthread_mutex_destroy(&(*data)->print_mutex);
	if ((*data)->last_meal_time_mutex_exists)
		pthread_mutex_destroy(&(*data)->last_meal_time_mutex);
	if ((*data)->dead_or_full_mutex_exists)
		pthread_mutex_destroy(&(*data)->dead_or_full_mutex);
	save_free((void **)data);
}

void	clean_up(t_data **data)
{
	if ((*data)->dinning_started)
		join_threads(data);
	free_philos(&(*data)->philo);
	destroy_data(data);
}
