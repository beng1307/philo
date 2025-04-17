/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:34:13 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/17 20:49:03 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (!(ac == 5 || ac == 6))
		return (error_message("Write the right amount of arguments!"), 1);
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (error_message("Allocation of data failed!"), 1);
	if (parse_and_init_philo(&data, av, ac) == 1)
		return (1);
	if (data->number_of_philos > 1)
		philo_while_loop(&data);
	else
		single_philo(&data);
	clean_up(&data);
}
