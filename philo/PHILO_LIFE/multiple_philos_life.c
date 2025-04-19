/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_philos_life.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:30:12 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/19 16:26:16 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	check_if_philo_is_full(t_philo *curr_philo)
{
	curr_philo->meal_counter++;
	pthread_mutex_lock(curr_philo->dead_or_full_mutex);
	if (*curr_philo->fifth_argument_exists)
	{
		if (curr_philo->meal_counter >= *curr_philo->times_phils_have_to_eat)
			curr_philo->done_eating = true;
	}
	pthread_mutex_unlock(curr_philo->dead_or_full_mutex);
}

static void	*philos_life(void *philo)
{
	t_philo	*curr_philo;

	curr_philo = (t_philo *)philo;
	pthread_mutex_lock(curr_philo->last_meal_time_mutex);
	curr_philo->last_meal_time = timestamp_in_ms();
	pthread_mutex_unlock(curr_philo->last_meal_time_mutex);
	if (curr_philo->id % 2)
		my_usleep(*curr_philo->time_to_eat / 2, curr_philo);
	while (1)
	{
		take_fork(curr_philo);
		eating(curr_philo);
		check_if_philo_is_full(curr_philo);
		sleeping(curr_philo);
		thinking(curr_philo);
		pthread_mutex_lock(curr_philo->dead_or_full_mutex);
		if (*curr_philo->philo_dead || *curr_philo->all_done_eating)
		{
			pthread_mutex_unlock(curr_philo->dead_or_full_mutex);
			break ;
		}
		pthread_mutex_unlock(curr_philo->dead_or_full_mutex);
	}
	return (NULL);
}

//Starts the dinning simulation of multiple philos
void	multiple_philos(t_data **data)
{
	size_t	index;

	index = 0;
	(*data)->starting_time = timestamp_in_ms();
	(*data)->dinning_started = true;
	while (index < (*data)->number_of_philos)
	{
		pthread_create(&(*data)->philo->philosopher, NULL, philos_life,
			(void *)(*data)->philo);
		my_another_usleep(200);
		(*data)->philo = (*data)->philo->next;
		index++;
	}
	if (monitor(data) == 1)
		return ;
}
