/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:24:24 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/04 17:35:28 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// • Because serving and eating spaghetti with only one fork is very inconvenient, a
// philosopher takes their right and their left forks to eat, one in each hand.
// • When a philosopher has finished eating, they put their forks back on the table and
// start sleeping. Once awake, they start thinking again. The simulation stops when
// a philosopher dies of starvation.
// • Every philosopher needs to eat and should never starve.
// • Philosophers don’t speak with each other.
// • Philosophers don’t know if another philosopher is about to die.


// Philosopher [i] wants to eat
// Philosopher [i] checks if left fork and right fork are available
// Philosopher [i] picks up forks (they become unavailable to i - 1 and i + 1)
// Philosopher [i] eats for time_to_eat miliseconds
// Philosopher [i] puts forks back (they become available again)
// Philosopher [i] sleeps for time_to_sleep miliseconds
// Philosopher [i] wakes up and starts thinking


// figure out:
// - way to keep track of which forks are available
// - way to keep track of how long philo hasn't eaten
// - how to make forks unavailable to other philo's

// ◦ timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died

bool	both_forks_available(t_philo *philo)
{
	if (philo->philo_nbr != philo->data->nbr_of_philosophers)
	{
	// check if left fork and right fork are available
	}
	else
	{
	// check if left fork and right fork are available
	}
	// lock forks
	// pick up forks
	// unlock forks

	// forks become unavailable while eating
}

void	philo_state_messages(int philo_state, t_philo *philo)
{
	struct timeval	current_time;

	pthread_mutex_lock(&philo->data->mutex);
	gettimeofday(&current_time, NULL);
	printf("philo = %i fork[%i] = %i!", philo->philo_nbr, philo->philo_nbr, *philo->data->forks[philo->philo_nbr]);
	if (philo_state == FORK)
		printf("%d %i has taken a fork\n", current_time.tv_usec, philo->philo_nbr);
	else if (philo_state == EATING)
		printf("%d %i is eating\n", current_time.tv_usec, philo->philo_nbr);
	else if (philo_state == SLEEPING)
		printf("%d %i is sleeping\n", current_time.tv_usec, philo->philo_nbr);
	else if (philo_state == THINKING)
		printf("%d %i is thinking\n", current_time.tv_usec, philo->philo_nbr);
	else if (philo_state == DIED)
		printf("%d %i died\n", current_time.tv_usec, philo->philo_nbr);
	pthread_mutex_unlock(&philo->data->mutex);
}

void	*routine(void *arguments)
{
	t_philo	*philo;

	philo = (t_philo *)arguments;
	*philo->data->forks[3] = UNAVAILABLE;
	if (philo->philo_nbr == 0)
		philo_state_messages(FORK, philo);
	if (philo->philo_nbr == 1)
		philo_state_messages(EATING, philo);
	if (philo->philo_nbr == 2)
		philo_state_messages(SLEEPING, philo);
	if (philo->philo_nbr == 3)
		philo_state_messages(THINKING, philo);
	if (philo->philo_nbr == 4)
		philo_state_messages(DIED, philo);

	while (true)
	{
		if (both_forks_available(philo))
		{
			// eat
		}
	// check if left fork and right fork are available
	// if availble, pick up forks
	// forks become unavailable while eating
	// eats for time_to_eat miliseconds
	// put forks back (they become available again)
	// sleep for time_to_sleep miliseconds
	// wakes up and starts thinking
	}

	//free (philo);
	return (NULL);
}
