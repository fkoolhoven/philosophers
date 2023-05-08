/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:23:37 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/08 15:39:12 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_state_message(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->message_mutex);
	if (philo->state == FORK)
		printf("philosopher %i has taken a fork\n", philo->philo_nbr);
	else if (philo->state == EATING)
		printf("philosopher %i is eating\n", philo->philo_nbr);
	else if (philo->state == SLEEPING)
		printf("philosopher %i is sleeping\n", philo->philo_nbr);
	else if (philo->state == THINKING)
		printf("philosopher %i is thinking\n", philo->philo_nbr);
	else if (philo->state == DIED)
		printf("philosopher %i died\n", philo->philo_nbr);
	pthread_mutex_unlock(&philo->data->message_mutex);
}

void	state_sleep(t_philo *philo)
{
	philo->state = SLEEPING;
	philo_state_message(philo);
	usleep(philo->data->time_to_sleep);
}

void	state_think(t_philo *philo)
{
	philo->state = THINKING;
	philo_state_message(philo);
}

void	state_eat(t_philo *philo)
{
	philo->state = EATING;
	philo_state_message(philo);
	usleep(philo->data->time_to_eat);
	*philo->data->forks[philo->right_fork] = AVAILABLE;
	*philo->data->forks[philo->left_fork] = AVAILABLE;
	pthread_mutex_unlock(philo->data->fork_mutexes[philo->right_fork]);
	pthread_mutex_unlock(philo->data->fork_mutexes[philo->left_fork]);
	philo->meals_had++;
}

void	state_fork(t_philo *philo)
{
	philo->state = FORK;
	philo_state_message(philo);
}
