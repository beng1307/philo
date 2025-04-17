/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:34:38 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/17 19:02:33 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	int	thinking_time;

	pthread_mutex_lock(philo->dead_or_full_mutex);
	if (!*philo->philo_dead && !philo->done_eating)
		safe_printf(philo, "is thinking");
	pthread_mutex_unlock(philo->dead_or_full_mutex);
	thinking_time = (*philo->time_to_die - *philo->time_to_eat
			- *philo->time_to_sleep) / 2;
	if (thinking_time > 200)
		thinking_time = 200;
	if (thinking_time > 0)
		my_usleep(thinking_time);
}

void	take_fork(t_philo *philo)
{
	if ((size_t)philo->id % 2)
	{
		pthread_mutex_lock(&philo->next->fork);
		pthread_mutex_lock(&philo->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
	}
	pthread_mutex_lock(philo->dead_or_full_mutex);
	if (!*philo->philo_dead && !philo->done_eating)
		safe_printf(philo, "has taken fork");
	pthread_mutex_unlock(philo->dead_or_full_mutex);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_or_full_mutex);
	if (!*philo->philo_dead && !philo->done_eating)
		safe_printf(philo, "is eating");
	pthread_mutex_unlock(philo->dead_or_full_mutex);
	pthread_mutex_lock(philo->last_meal_time_mutex);
	philo->last_meal_time = timestamp_in_ms();
	pthread_mutex_unlock(philo->last_meal_time_mutex);
	my_usleep(*philo->time_to_eat);
	if ((size_t)philo->id % 2)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
	}
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_or_full_mutex);
	if (!*philo->philo_dead && !philo->done_eating)
		safe_printf(philo, "is sleeping");
	pthread_mutex_unlock(philo->dead_or_full_mutex);
	my_usleep(*philo->time_to_sleep);
}

void	died(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_or_full_mutex);
	safe_printf(philo, "died");
	*philo->philo_dead = true;
	pthread_mutex_unlock(philo->dead_or_full_mutex);
}
