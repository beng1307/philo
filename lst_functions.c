/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:34:05 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/17 20:01:57 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_philo	*ft_newphilo(int id)
{
	t_philo	*new_philo;

	new_philo = ft_calloc(1, sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	if (pthread_mutex_init(&new_philo->fork, NULL) != 0)
		return (save_free((void **)new_philo), NULL);
	new_philo->id = id;
	new_philo->meal_counter = 0;
	new_philo->done_eating = false;
	new_philo->next = NULL;
	new_philo->prev = NULL;
	return (new_philo);
}

int	philo_add_back(t_philo **philo_list, t_philo *new_philo)
{
	t_philo	*last_philo;

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

t_philo	*create_philos(size_t number_of_philos)
{
	t_philo	*list_of_philos;
	t_philo	*last_philo;
	size_t	index;

	index = 0;
	list_of_philos = NULL;
	while (index < number_of_philos)
	{
		if (philo_add_back(&list_of_philos, ft_newphilo(index + 1)) == 1)
			return (free_philos(&list_of_philos), NULL);
		index++;
	}
	last_philo = ft_last_philo(list_of_philos);
	list_of_philos->prev = last_philo;
	last_philo->next = list_of_philos;
	return (list_of_philos);
}
