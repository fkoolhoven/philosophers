/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:32:48 by felicia           #+#    #+#             */
/*   Updated: 2023/06/13 14:35:17 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h> 
# include <unistd.h> 
# include <stdbool.h>

// =====MACROS==================================================================

# define FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4

// =====STRUCTS=================================================================

typedef struct s_data
{
	long long		start_time;
	long long		time_to_starve;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				initialized_threads;
	int				philosophers_amount;
	int				forks_amount;
	int				meals_quota;
	bool			initialization_failed;
	bool			meals_quota_established;
	bool			dinner_should_start;
	bool			dinner_should_end;
	pthread_mutex_t	message_mutex;
	pthread_mutex_t	dinner_start_mutex;
	pthread_mutex_t	dinner_end_mutex;
	pthread_mutex_t	**fork_mutexes;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	int				state;
	int				right_fork;
	int				left_fork;
	int				last_meal;
	int				meals_had;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	meals_had_mutex;
	pthread_mutex_t	state_mutex;
}	t_philo;

typedef struct s_thread_args
{
	t_data	*data;
	t_philo	*philo;
}	t_thread_args;

// =====FUNCTIONS===============================================================

// input_validation.c
bool		input_validation(t_data *data);

// initialize_data.c
t_data		*store_arguments_in_data_struct(int argc, char **argv);
void		*initialize_mutexes_in_data_struct(t_data *data);

// error_messages.c
void		print_input_error_message(char *error_message);
void		print_error_message(char *message);
void		*print_error_message_and_return_null(char *message);

// initialize_threads.c
t_philo		**initialize_philosopher_threads(t_data *data);

// general_utils.c
long long	ft_atol(const char *str);

// time_utils.c
long long	get_current_time(void);
long long	get_simulation_time(t_data *data);
void		let_time_pass(long long time_to_sleep, t_data *data);

// dining_threads.c
void		*dining_thread_main(void *args_pointer);

// dinner_start_end.c
void		let_dinner_start(t_data *data);
bool		should_dinner_start(t_data *data);
bool		should_dinner_end(t_data *data);

// philo_states.c
void		state_fork(t_philo *philo, t_data *data);
void		state_eat(t_philo *philo, t_data *data);
void		state_sleep(t_philo *philo, t_data *data);
void		state_think(t_philo *philo, t_data *data);
void		state_died(t_philo *philo, t_data *data);

// log_messages.c
void		print_philo_state_message(t_philo *philo, t_data *data);
void		print_meals_quota_message(t_data *data);

// monitor_dining.c
void		monitor_dining(t_philo **philos, t_data *data);

// clean_memory.c
void		join_philosopher_threads(t_philo **philo, t_data *data);
void		free_memory(t_philo **philo, t_data *data);

#endif