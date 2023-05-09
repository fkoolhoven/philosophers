/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:24:24 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/09 17:41:43 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	get_both_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->data->fork_mutexes[philo->right_fork]);
	state_fork(philo);
	pthread_mutex_lock(philo->data->fork_mutexes[philo->left_fork]);
	state_fork(philo);
	return (true);
}

void	*dining(void *arguments)
{
	t_philo	*philo;

	philo = (t_philo *)arguments;
	state_think(philo);
	if (philo->philo_nbr % 2 == 0)
		precise_usleep(philo->data->time_to_eat);
	while (true)
	{
		if (get_both_forks(philo))
		{
			state_eat(philo);
			state_sleep(philo);
			state_think(philo);
		}
	}
	// free (philo);
	return (NULL);
}
