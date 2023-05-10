/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:24:24 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/10 12:20:25 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	get_both_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->fork_mutexes[philo->right_fork]);
	state_fork(philo, data);
	pthread_mutex_lock(data->fork_mutexes[philo->left_fork]);
	state_fork(philo, data);
	return (true);
}

void	dining_routine(t_philo *philo, t_data *data)
{

	state_think(philo, data);
	if (philo->philo_id % 2 == 0)
		let_time_pass(data->time_to_eat, data);
	while (true)
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
	dining_routine(philo, data);
	return (NULL);
}
