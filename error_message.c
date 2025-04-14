#include "philo.h"

void	error_message(char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}
