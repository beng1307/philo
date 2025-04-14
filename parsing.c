#include "philo.h"

t_philo	*create_philos(size_t number_of_philos)
{
	t_philo	*list_of_philos;
	t_philo	*last_philo;
	size_t	index;

	index = 0;
	list_of_philos = NULL;
	while (index < number_of_philos)
	{
		if (philo_add_back(&list_of_philos, ft_newphilo(index + 1)) == 1)
			return (free_philos(&list_of_philos), NULL);
		index++;
	}
	last_philo = ft_last_philo(list_of_philos);
	list_of_philos->prev = last_philo;
	last_philo->next = list_of_philos;
	return (list_of_philos);
}

static int number_validation(t_data **data)
{
	if ((*data)->number_of_philos < 1)
		return (1);
	if ((*data)->time_to_die < 1)
		return (1);
	if ((*data)->time_to_eat < 1)
		return (1);
	if ((*data)->time_to_sleep < 1)
		return (1);
	if ((*data)->times_phils_have_to_eat < 1)
		return (1);
	
	return (0);
}

static void	inform_philos(t_data **data)
{
	size_t	index;
	t_philo	*curr_philo;

	index = 0;
	curr_philo = (*data)->philo;
	while (index < (*data)->number_of_philos)	
	{
		curr_philo->print_mutex = &(*data)->print_mutex;
		curr_philo->last_meal_time_mutex = &(*data)->last_meal_time_mutex;
		curr_philo->philo_dead_mutex = &(*data)->philo_dead_mutex;
		curr_philo->number_of_philos = &(*data)->number_of_philos;
		curr_philo->time_to_eat = &(*data)->time_to_eat;
		curr_philo->time_to_sleep = &(*data)->time_to_sleep;
		curr_philo->time_to_die = &(*data)->time_to_die;
		curr_philo->times_phils_have_to_eat = &(*data)->times_phils_have_to_eat;
		curr_philo->starting_time = &(*data)->starting_time;
		curr_philo->philo_dead = &(*data)->philo_dead;

		curr_philo = curr_philo->next;
		index++;
	}
}


int	parse_and_init_philo(t_data **data, char **av)
{
	(*data)->number_of_philos = philo_atoi(av[1]);
	(*data)->time_to_die = philo_atoi(av[2]);
	(*data)->time_to_eat = philo_atoi(av[3]);
	(*data)->time_to_sleep = philo_atoi(av[4]);
	(*data)->times_phils_have_to_eat = philo_atoi(av[4]);
	(*data)->philo_dead = false;
	(*data)->dinning_started = false;

	(*data)->print_mutex_exists = false;
	(*data)->philo_dead_mutex_exists = false;
	(*data)->last_meal_time_mutex_exists = false;

	if (pthread_mutex_init(&(*data)->print_mutex, NULL) != 0)
		return (clean_up(data), 1);
	(*data)->print_mutex_exists = true;
	if (pthread_mutex_init(&(*data)->philo_dead_mutex, NULL) != 0)
		return (clean_up(data), 1);
	(*data)->philo_dead_mutex_exists = true;
	if (pthread_mutex_init(&(*data)->last_meal_time_mutex, NULL) != 0)
		return (clean_up(data), 1);
	(*data)->last_meal_time_mutex_exists = true;

	(*data)->philo = create_philos((*data)->number_of_philos);
	if (!(*data)->philo)
		return (clean_up(data), 1);
	inform_philos(data);

	return (number_validation(data));
}
