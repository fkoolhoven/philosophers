/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:24:24 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/22 17:45:30 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	get_both_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->fork_mutexes[philo->right_fork]);
	state_fork(philo, data);
	pthread_mutex_lock(data->fork_mutexes[philo->left_fork]);
	state_fork(philo, data);
	return (true);
}

static void	dining_routine(t_philo *philo, t_data *data)
{
	state_think(philo, data);
	if (philo->philo_id % 2 == 0)
		let_time_pass(data->time_to_eat, data);
	while (!should_dinner_end(data))
	{
		if (get_both_forks(philo, data))
		{
			state_eat(philo, data);
			state_sleep(philo, data);
			state_think(philo, data);
		}
	}
}

void	*dining_thread_start(void *args_pointer)
{
	t_thread_args	*arguments;
	t_philo			*philo;
	t_data			*data;

	arguments = (t_thread_args *)args_pointer;
	philo = arguments->philo;
	data = arguments->data;
	free(arguments);
	while (!should_dinner_start(data))
		;
	if (data->forks_amount == 1)
	{
		let_time_pass(data->time_to_starve, data);
		state_died(philo, data);
	}
	dining_routine(philo, data);
	pthread_mutex_destroy(&philo->state_mutex);
	pthread_mutex_destroy(&philo->last_meal_mutex);
	pthread_mutex_destroy(&philo->meals_had_mutex);
	free(philo);
	return (NULL);
}
