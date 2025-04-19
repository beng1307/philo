/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:16:15 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/19 16:26:31 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	safe_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%zu %d %s\n", timestamp_in_ms() - *philo->starting_time, philo->id,
		str);
	pthread_mutex_unlock(philo->print_mutex);
}

void	error_message(char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}
