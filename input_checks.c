#include "philo.h"

int	an_arg_is_not_correct(char **av)
{
	size_t	index1;
	size_t	index2;

	index1 = 0;
	index2 = 0;
	while (av[index1])
	{
		while (av[index2])
		{
			if (is_not_a_digit(*av[index2]))
				return (1);
			index2++;
		}
		index1++;	
	}
	return (0);
}

int	wrong_input(int ac, char **av)
{
	if (!(ac == 5 || ac == 6))
		return (1);
	if (an_arg_is_not_correct(av))
		return (1);
	return (0);
}
