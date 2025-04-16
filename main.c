#include "philo.h"

static void	*philos_life(void *philo)
{
	t_philo	*curr_philo;
	
	curr_philo = (t_philo *)philo;
	pthread_mutex_lock(curr_philo->last_meal_time_mutex);
	curr_philo->last_meal_time = timestamp_in_ms();
	pthread_mutex_unlock(curr_philo->last_meal_time_mutex);	

	if (curr_philo->id % 2)
		my_usleep(1);
	while (1)
	{
		take_fork(curr_philo);
		eating(curr_philo);
		curr_philo->meal_counter++;
		// printf("%zu\n", curr_philo->meal_counter);
		// printf("times he has to eat %zu\n", *curr_philo->times_phils_have_to_eat);
		if (*curr_philo->fifth_argument_exists)
		{
			if (curr_philo->meal_counter >= *curr_philo->times_phils_have_to_eat)
				return (NULL);
		}
		sleeping(curr_philo);
		thinking(curr_philo);
		pthread_mutex_lock(curr_philo->philo_dead_mutex);
		if (*curr_philo->philo_dead)
		{
			pthread_mutex_unlock(curr_philo->philo_dead_mutex);
			break ;
		}
		pthread_mutex_unlock(curr_philo->philo_dead_mutex);
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
		my_usleep(1);
		(*data)->philo = (*data)->philo->next;
		index++;		
	}
	if (!all_alive(data))
		return ;
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (error_message("Allocation of data failed!"), 1);
	if (wrong_input(ac, &av[1]))
		return (free(data), error_message("Put only numbers!"), 1);
	if (parse_and_init_philo(&data, av, ac) == 1)
		return (error_message("Input not valid!"), 1);
	if (data->number_of_philos > 1)
		philo_while_loop(&data);
	else
		single_philo(&data);
	clean_up(&data);
}
