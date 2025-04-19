/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:34:47 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/19 16:26:26 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*terminate;

	i = 0;
	terminate = (char *)s;
	while (i < n)
	{
		*terminate = '\0';
		terminate++;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memp;

	if (!nmemb || !size)
		return (malloc(0));
	if (nmemb * size <= SIZE_MAX)
	{
		memp = malloc(nmemb * size);
		if (memp == NULL)
			return (NULL);
		ft_bzero(memp, nmemb * size);
	}
	else
		return (NULL);
	return (memp);
}

bool	is_not_a_digit(char character)
{
	return (!(character >= '0' && character <= '9'));
}

size_t	ft_strlen(char *str)
{
	size_t	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

size_t	philo_atoi(const char *str)
{
	size_t	number;

	number = 0;
	while (*str)
	{
		if (number > SIZE_MAX / 10)
			return (SIZE_MAX);
		if ((number == SIZE_MAX / 10
				&& (size_t)(*str++ - '0') > SIZE_MAX % 10))
			return (SIZE_MAX);
		number = number * 10 + (*str++ - '0');
	}
	return (number);
}
