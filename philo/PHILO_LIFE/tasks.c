/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:34:38 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/26 14:09:13 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	thinking(t_philo *philo)
{
	size_t	time_to_think;

	pthread_mutex_lock(philo->dead_or_full_mutex);
	if (!*philo->philo_dead && !philo->done_eating)
		safe_printf(philo, "is thinking");
	pthread_mutex_unlock(philo->dead_or_full_mutex);
	time_to_think = (*philo->time_to_die - *philo->time_to_eat
			- *philo->time_to_sleep) / 2;
	if (time_to_think < 1)
		time_to_think = 1;
	my_usleep(time_to_think, philo);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		pthread_mutex_lock(&philo->fork);
	}
	pthread_mutex_lock(philo->dead_or_full_mutex);
	if (!*philo->philo_dead && !philo->done_eating)
	{
		safe_printf(philo, "has taken fork");
		safe_printf(philo, "has taken fork");
	}
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
	my_usleep(*philo->time_to_eat, philo);
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
	my_usleep(*philo->time_to_sleep, philo);
}

void	died(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_or_full_mutex);
	safe_printf(philo, "died");
	*philo->philo_dead = true;
	pthread_mutex_unlock(philo->dead_or_full_mutex);
}
