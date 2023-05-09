/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:24:24 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/09 19:43:21 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_if_philosopher_starved(t_philo *philo, t_data *data)
{
	int	time_since_last_meal;

	time_since_last_meal = get_simulation_time(data) - philo->last_meal_time;
	if (time_since_last_meal > data->time_to_starve)
		return (true);
	return (false);
}

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
		let_time_pass(data->time_to_eat);
	while (true)
	{
		if (check_if_philosopher_starved(philo, data) == true)
		{
			printf("last meal time for philo %i = %i\n", philo->philo_id, philo->last_meal_time);
			state_died(philo, data);
			exit (0);
		}
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
