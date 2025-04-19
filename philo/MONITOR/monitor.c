/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:12:57 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/19 16:26:36 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	philos_still_alive(t_data **data,
		t_philo *curr_philo, size_t *hunger_time)
{
	pthread_mutex_lock(&(*data)->last_meal_time_mutex);
	*hunger_time = timestamp_in_ms() - curr_philo->last_meal_time;
	if (*hunger_time > (*data)->time_to_die)
		return (pthread_mutex_unlock(&(*data)->last_meal_time_mutex),
			died(curr_philo), false);
	pthread_mutex_unlock(&(*data)->last_meal_time_mutex);
	return (true);
}

static void	count_full_philos(t_philo *curr_philo,
		size_t *index, size_t *full_philos)
{
	pthread_mutex_lock(curr_philo->dead_or_full_mutex);
	if (curr_philo->done_eating)
		(*full_philos)++;
	(*index)++;
	pthread_mutex_unlock(curr_philo->dead_or_full_mutex);
}

static bool	philos_still_hungry(t_data **data,
		size_t *index, size_t *full_philos)
{
	pthread_mutex_lock(&(*data)->dead_or_full_mutex);
	if (*index == (*data)->number_of_philos
		&& *full_philos == (*data)->number_of_philos)
	{
		(*data)->all_done_eating = true;
		return (pthread_mutex_unlock(&(*data)->dead_or_full_mutex),
			false);
		printf("test 1\n");
	}
	else if (*index == (*data)->number_of_philos
		&& *full_philos != (*data)->number_of_philos)
	{
		*index = 0;
		*full_philos = 0;
	}
	pthread_mutex_unlock(&(*data)->dead_or_full_mutex);
	return (true);
}

//Monitors the wellbeing of the philos
/* monitor.c */
int	monitor(t_data **data)
{
	t_philo	*philos;
	size_t	index;
	size_t	hunger_time;
	size_t	full_philos;

	philos = (*data)->philo;
	index = 0;
	hunger_time = 0;
	full_philos = 0;
	while (1)
	{
		if (!philos_still_alive(data, philos, &hunger_time))
			return (1);
		count_full_philos(philos, &index, &full_philos);
		if (!philos_still_hungry(data, &index, &full_philos))
			return (1);
		philos = philos->next;
		usleep(1000);
	}
	return (0);
}
