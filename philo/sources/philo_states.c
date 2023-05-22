/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:23:37 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/22 16:26:29 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/colors.h"

void	state_died(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = DIED;
	pthread_mutex_unlock(&philo->state_mutex);
	print_philo_state_message(philo, data);
}

void	state_think(t_philo *philo, t_data *data)
{
	if (should_dinner_end(data))
		return ;
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->state_mutex);
	print_philo_state_message(philo, data);
}

void	state_sleep(t_philo *philo, t_data *data)
{
	if (should_dinner_end(data))
		return ;
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->state_mutex);
	print_philo_state_message(philo, data);
	let_time_pass(data->time_to_sleep, data);
}

void	state_eat(t_philo *philo, t_data *data)
{
	if (should_dinner_end(data))
	{
		pthread_mutex_unlock(data->fork_mutexes[philo->right_fork]);
		pthread_mutex_unlock(data->fork_mutexes[philo->left_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->state_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_simulation_time(data);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	print_philo_state_message(philo, data);
	let_time_pass(data->time_to_eat, data);
	pthread_mutex_unlock(data->fork_mutexes[philo->right_fork]);
	pthread_mutex_unlock(data->fork_mutexes[philo->left_fork]);
	pthread_mutex_lock(&philo->meals_had_mutex);
	philo->meals_had++;
	pthread_mutex_unlock(&philo->meals_had_mutex);
}

void	state_fork(t_philo *philo, t_data *data)
{
	if (should_dinner_end(data))
		return ;
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = FORK;
	pthread_mutex_unlock(&philo->state_mutex);
	print_philo_state_message(philo, data);
}
