/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:34:02 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/19 16:25:54 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//Checks if the input are only digits
int	an_arg_is_not_correct(char **av)
{
	size_t	index1;
	size_t	index2;

	index1 = 0;
	index2 = 0;
	while (av[index1])
	{
		while (av[index1][index2])
		{
			if (is_not_a_digit(av[index1][index2]))
				return (1);
			index2++;
		}
		index2 = 0;
		index1++;
	}
	return (0);
}
