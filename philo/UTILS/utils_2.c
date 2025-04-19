/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:04:17 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/19 16:26:29 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	timestamp_in_ms(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}

void	my_usleep(size_t time_in_ms, t_philo *philo)
{
	size_t	curr_timestamp;

	curr_timestamp = timestamp_in_ms();
	while ((timestamp_in_ms() - curr_timestamp) < time_in_ms)
	{
		usleep(500);
		pthread_mutex_lock(philo->dead_or_full_mutex);
		if (*philo->philo_dead)
		{
			pthread_mutex_unlock(philo->dead_or_full_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->dead_or_full_mutex);
	}
}

size_t	timestamp_in_us(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return (curr_time.tv_sec * 1000000UL + curr_time.tv_usec);
}

void	my_another_usleep(size_t time_in_us)
{
	size_t	curr_timestamp;

	curr_timestamp = timestamp_in_us();
	while ((timestamp_in_us() - curr_timestamp) < time_in_us)
		usleep(50);
}
