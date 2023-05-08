/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:24:24 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/08 16:35:21 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	get_both_forks(t_philo *philo)
{
	if (*philo->data->forks[philo->right_fork] == AVAILABLE
		&& *philo->data->forks[philo->left_fork] == AVAILABLE)
	{
		pthread_mutex_lock(philo->data->fork_mutexes[philo->right_fork]);
		*philo->data->forks[philo->right_fork] = UNAVAILABLE;
		state_fork(philo);
		if (*philo->data->forks[philo->left_fork] == AVAILABLE)
		{
			pthread_mutex_lock(philo->data->fork_mutexes[philo->left_fork]);
			*philo->data->forks[philo->left_fork] = UNAVAILABLE;
			state_fork(philo);
			return (true);
		}
		else
		{
			*philo->data->forks[philo->right_fork] = AVAILABLE;
			pthread_mutex_unlock(philo->data->fork_mutexes[philo->right_fork]);
			state_think(philo);
		}
	}
	return (false);
}

void	*dining(void *arguments)
{
	t_philo	*philo;

	philo = (t_philo *)arguments;
	state_think(philo);
	while (true)
	{
		// if (!check_if_alive(philo))
		// {
			
		// }
		if (get_both_forks(philo))
		{
			state_eat(philo);
			state_sleep(philo);
			state_think(philo);
		}
	}
	//free (philo);
	return (NULL);
}
