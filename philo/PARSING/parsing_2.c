/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:09:45 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/19 16:26:13 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	number_validation(t_data **data)
{
	if ((*data)->number_of_philos < 1 || (*data)->number_of_philos > 200)
		return (1);
	if ((*data)->time_to_die < 60)
		return (1);
	if ((*data)->time_to_eat < 60)
		return (1);
	if ((*data)->time_to_sleep < 60)
		return (1);
	if ((*data)->fifth_argument_exists)
	{
		if ((*data)->times_phils_have_to_eat < 1)
			return (1);
	}
	return (0);
}

int	parse_input(t_data **data, char **av, int ac)
{
	(*data)->number_of_philos = philo_atoi(av[1]);
	(*data)->time_to_die = philo_atoi(av[2]);
	(*data)->time_to_eat = philo_atoi(av[3]);
	(*data)->time_to_sleep = philo_atoi(av[4]);
	if (ac == 5)
		(*data)->fifth_argument_exists = false;
	else if (ac == 6)
	{
		(*data)->fifth_argument_exists = true;
		(*data)->times_phils_have_to_eat = philo_atoi(av[5]);
	}
	return (number_validation(data));
}

void	init_vars(t_data **data)
{
	(*data)->philo_dead = false;
	(*data)->dinning_started = false;
	(*data)->all_done_eating = false;
	(*data)->print_mutex_exists = false;
	(*data)->dead_or_full_mutex_exists = false;
	(*data)->last_meal_time_mutex_exists = false;
}

int	init_mutexes(t_data **data)
{
	if (pthread_mutex_init(&(*data)->print_mutex, NULL) != 0)
		return (clean_up(data), 1);
	(*data)->print_mutex_exists = true;
	if (pthread_mutex_init(&(*data)->dead_or_full_mutex, NULL) != 0)
		return (clean_up(data), 1);
	(*data)->dead_or_full_mutex_exists = true;
	if (pthread_mutex_init(&(*data)->last_meal_time_mutex, NULL) != 0)
		return (clean_up(data), 1);
	(*data)->last_meal_time_mutex_exists = true;
	return (0);
}

void	inform_philos(t_data **data)
{
	size_t	index;
	t_philo	*curr_philo;

	index = 0;
	curr_philo = (*data)->philo;
	while (index < (*data)->number_of_philos)
	{
		curr_philo->print_mutex = &(*data)->print_mutex;
		curr_philo->last_meal_time_mutex = &(*data)->last_meal_time_mutex;
		curr_philo->dead_or_full_mutex = &(*data)->dead_or_full_mutex;
		curr_philo->number_of_philos = &(*data)->number_of_philos;
		curr_philo->time_to_eat = &(*data)->time_to_eat;
		curr_philo->time_to_sleep = &(*data)->time_to_sleep;
		curr_philo->time_to_die = &(*data)->time_to_die;
		curr_philo->times_phils_have_to_eat = &(*data)->times_phils_have_to_eat;
		curr_philo->starting_time = &(*data)->starting_time;
		curr_philo->philo_dead = &(*data)->philo_dead;
		curr_philo->fifth_argument_exists = &(*data)->fifth_argument_exists;
		curr_philo->all_done_eating = &(*data)->all_done_eating;
		curr_philo = curr_philo->next;
		index++;
	}
}
