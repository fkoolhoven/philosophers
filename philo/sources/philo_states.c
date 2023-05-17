/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:23:37 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/17 15:49:19 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/colors.h"

void	state_sleep(t_philo *philo, t_data *data)
{
	philo->state = SLEEPING;
	print_philo_state_message(philo, data);
	let_time_pass(data->time_to_sleep, data);
}

void	state_think(t_philo *philo, t_data *data)
{
	philo->state = THINKING;
	print_philo_state_message(philo, data);
}

void	state_eat(t_philo *philo, t_data *data)
{
	philo->state = EATING;
	print_philo_state_message(philo, data);
	philo->last_meal = get_simulation_time(data);
	let_time_pass(data->time_to_eat, data);
	pthread_mutex_unlock(data->fork_mutexes[philo->right_fork]);
	pthread_mutex_unlock(data->fork_mutexes[philo->left_fork]);
	philo->meals_had++;
}

void	state_fork(t_philo *philo, t_data *data)
{
	philo->state = FORK;
	print_philo_state_message(philo, data);
}

void	state_died(t_philo *philo, t_data *data)
{
	philo->state = DIED;
	print_philo_state_message(philo, data);
}
