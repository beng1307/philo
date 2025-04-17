/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:04:17 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/17 18:28:46 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_message(char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

size_t	timestamp_in_ms(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}

void	safe_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%zu %d %s\n", timestamp_in_ms() - *philo->starting_time, philo->id,
		str);
	pthread_mutex_unlock(philo->print_mutex);
}

void	my_usleep(size_t time_in_ms)
{
	size_t	curr_timestamp;

	curr_timestamp = timestamp_in_ms();
	while ((timestamp_in_ms() - curr_timestamp) < time_in_ms)
		usleep(500);
}
