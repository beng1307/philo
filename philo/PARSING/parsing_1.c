/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:34:23 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/19 16:26:10 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	parse_and_init_philo(t_data **data, char **av, int ac)
{
	if (an_arg_is_not_correct(&av[1]))
		return (free(*data), error_message("Put only numbers!"), 1);
	if (parse_input(data, av, ac) == 1)
		return (error_message("Input not valid!"), 1);
	init_vars(data);
	if (init_mutexes(data) == 1)
		return (error_message("Mutex initialization failed!"), 1);
	(*data)->philo = create_philos((*data)->number_of_philos);
	if (!(*data)->philo)
		return (clean_up(data), error_message("Creating Philos failed!"), 1);
	inform_philos(data);
	return (0);
}
