#include "philo.h"

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
		if (number > (SIZE_MAX - (*str - '0') / 10)) //Maybe it should be a *
			return (SIZE_MAX);
		number = number * 10 + (*str++ - '0');
	}
	return (number);
}

size_t timestamp_in_ms(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}

void	safe_printf(t_philo *philo, char *str)
{ 
 	pthread_mutex_lock(philo->print_mutex);
	if (!*philo->philo_dead)
		printf("%zu %d %s\n", timestamp_in_ms() - *philo->starting_time, philo->id, str);
 	pthread_mutex_unlock(philo->print_mutex);
}
