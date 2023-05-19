/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:24:24 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/19 14:59:57 by fkoolhov         ###   ########.fr       */
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
	while (!data->dinner_should_stop)
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
	t_thread_arguments	*arguments;
	t_philo				*philo;
	t_data				*data;

	arguments = (t_thread_arguments *)args_pointer;
	philo = arguments->philo;
	data = arguments->data;
	free(arguments);
	while (!data->all_philosophers_present)
		;
	if (data->forks_amount == 1)
	{
		let_time_pass(data->time_to_starve, data);
		state_died(philo, data);
	}
	dining_routine(philo, data);
	free(philo);
	return (NULL);
}
