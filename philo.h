/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:40:44 by bgretic           #+#    #+#             */
/*   Updated: 2025/04/18 14:36:41 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// Structs
typedef struct s_philo
{
	pthread_t		philosopher;
	int				id;

	pthread_mutex_t	fork;
	size_t			last_meal_time;
	size_t			meal_counter;
	bool			done_eating;

	struct s_philo	*prev;
	struct s_philo	*next;

	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*last_meal_time_mutex;
	pthread_mutex_t	*dead_or_full_mutex;
	size_t			*number_of_philos;
	size_t			*time_to_eat;
	size_t			*time_to_sleep;
	size_t			*time_to_die;
	size_t			*times_phils_have_to_eat;
	size_t			*starting_time;
	bool			*philo_dead;
	bool			*fifth_argument_exists;
	bool			*all_done_eating;

}					t_philo;

typedef struct s_data
{
	t_philo			*philo;

	pthread_mutex_t	print_mutex;
	bool			print_mutex_exists;
	pthread_mutex_t	last_meal_time_mutex;
	bool			last_meal_time_mutex_exists;
	pthread_mutex_t	dead_or_full_mutex;
	bool			dead_or_full_mutex_exists;

	size_t			number_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			times_phils_have_to_eat;
	size_t			starting_time;

	bool			philo_dead;
	bool			dinning_started;
	bool			fifth_argument_exists;
	bool			all_done_eating;
}					t_data;

// Utils
void				save_free(void **to_free);
size_t				ft_strlen(char *str);
size_t				philo_atoi(const char *str);
void				*ft_calloc(size_t nmemb, size_t size);
size_t				timestamp_in_ms(void);
bool				is_not_a_digit(char character);
void				safe_printf(t_philo *philo, char *str);
void				my_usleep(size_t milliseconds, t_philo *philo);

// Error handling
int					an_arg_is_not_correct(char **av);
void				error_message(char *message);

// Linked-list functions
t_philo				*ft_newphilo(int id);
t_philo				*ft_last_philo(t_philo *philo);
int					philo_add_back(t_philo **philo_list, t_philo *new_philo);
t_philo				*create_philos(size_t number_of_philos);

// Tasks
void				thinking(t_philo *philo);
void				take_fork(t_philo *philo);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				died(t_philo *philo);
int					monitor(t_data **data);

// Parsing
int					parse_and_init_philo(t_data **data, char **av, int ac);
void				inform_philos(t_data **data);
int					init_mutexes(t_data **data);
int					number_validation(t_data **data);
int					parse_input(t_data **data, char **av, int ac);
void				init_vars(t_data **data);

// Clean up
void				clean_up(t_data **data);
void				free_philos(t_philo **philo, size_t number_of_philos);

// Logic
void				single_philo(t_data **data);
void				philo_while_loop(t_data **data);

#endif