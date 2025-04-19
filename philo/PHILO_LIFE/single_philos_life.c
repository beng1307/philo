/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philos_life.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:34:34 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/19 16:26:19 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	*single_philos_life(void *philo)
{
	t_philo	*curr_philo;

	curr_philo = (t_philo *)philo;
	pthread_mutex_lock(&curr_philo->fork);
	safe_printf(curr_philo, "has taken fork");
	my_usleep(*curr_philo->time_to_die, curr_philo);
	safe_printf(curr_philo, "died");
	pthread_mutex_unlock(&curr_philo->fork);
	return (NULL);
}

//Starts the dinning simulation of a single philos
void	single_philo(t_data **data)
{
	(*data)->starting_time = timestamp_in_ms();
	(*data)->dinning_started = true;
	pthread_create(&(*data)->philo->philosopher, NULL, single_philos_life,
		(void *)(*data)->philo);
}
