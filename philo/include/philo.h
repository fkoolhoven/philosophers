/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:32:48 by felicia           #+#    #+#             */
/*   Updated: 2023/05/19 14:53:21 by fkoolhov         ###   ########.fr       */
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
	bool			all_philosophers_present;
	long long		start_time;
	int				philosophers_amount;
	int				forks_amount;
	long long		time_to_starve;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				meals_quota;
	bool			meals_quota_established;
	bool			dinner_should_stop;
	pthread_mutex_t	message_mutex;
	pthread_mutex_t	**fork_mutexes;
}	t_data;

typedef struct s_philo
{
	pthread_t	thread;
	int			philo_id;
	int			state;
	int			right_fork;
	int			left_fork;
	int			last_meal;
	int			meals_had;
}	t_philo;

typedef struct s_thread_arguments
{
	t_data	*data;
	t_philo	*philo;
}	t_thread_arguments;

// =====FUNCTIONS===============================================================

// input_validation.c
void		input_validation(t_data *data);

// initialize_data.c
t_data		*store_arguments_in_data_struct(int argc, char **argv);
void		initialize_mutexes(t_data *data);

// handle_errors.c
void		print_input_error_message_and_exit(char *error_message);
void		print_error_message_and_exit(char *message);

// initialize_threads.c
t_philo		**initialize_philosopher_threads(t_data *data);

// general_utils.c
long long	ft_atol(const char *str);

// time_utils.c
long long	get_current_time(void);
long long	get_simulation_time(t_data *data);
void		let_time_pass(long long time_to_sleep, t_data *data);

// dining_threads.c
void		*dining_thread_start(void *args_pointer);

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

// cleanup.c
void		join_philosopher_threads(t_philo **philo, t_data *data);
void		free_memory(t_philo **philo, t_data *data);


#endif