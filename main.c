#include "philo.h"

static void	*philos_life(void *philo)
{
	t_philo	*curr_philo;
	
	curr_philo = (t_philo *)philo;
	curr_philo->last_meal_time = timestamp_in_ms();	

	while (1)
	{
		take_fork(curr_philo);
		eating(curr_philo);
		sleeping(curr_philo);
		thinking(curr_philo);
	}
	return (NULL);
}

static void	philo_while_loop(t_data **data)
{
	size_t	index;

	index = 0;
	(*data)->starting_time = timestamp_in_ms();
	(*data)->dinning_started = true;
	while (index < (*data)->number_of_philos)
	{
		pthread_create(&(*data)->philo->philosopher, NULL, philos_life, (void *)(*data)->philo);
		(*data)->philo = (*data)->philo->next;
		index++;		
	}
	while (1)
	{
		if (!all_alive(data))
			break ;
	}
}

// static void	single_philo_loop(t_data **data)
// {

// }

int	main(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (error_message("Allocation of data failed!"), 1);
	if (wrong_input(ac, &av[1]))
		return (free(data), error_message("Put only numbers!"), 1);
	if (parse_and_init_philo(&data, av) == 1)
		return (error_message("Input not valid!"), 1);
	if (data->number_of_philos > 1)
		philo_while_loop(&data);
	// else
	// 	single_philo_loop();
	clean_up(&data);
}
