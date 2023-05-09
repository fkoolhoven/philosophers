/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:23:37 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/09 18:53:47 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/colors.h"

void	print_philo_state_message(t_philo *philo, t_data *data)
{
	char		*state;
	long long	current_time;

	pthread_mutex_lock(&data->message_mutex);
	state = NULL;
	if (philo->state == FORK)
		state = CC_CYAN"has taken a fork"CC_OFF;
	else if (philo->state == EATING)
		state = CC_GREEN"is eating"CC_OFF;
	else if (philo->state == SLEEPING)
		state = CC_MAGENTA"is sleeping"CC_OFF;
	else if (philo->state == THINKING)
		state = CC_BLUE"is thinking"CC_OFF;
	else if (philo->state == DIED)
		state = CC_RED"died"CC_OFF;
	current_time = get_current_time() - data->start_time;
	printf("%llu "CC_YELLOW"%i "CC_OFF""CC_BOLD"%s\n"CC_OFF,
		current_time, philo->philo_id, state);
	pthread_mutex_unlock(&data->message_mutex);
}

void	state_sleep(t_philo *philo, t_data *data)
{
	philo->state = SLEEPING;
	print_philo_state_message(philo, data);
	let_time_pass(data->time_to_sleep);
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
	let_time_pass(data->time_to_eat);
	pthread_mutex_unlock(data->fork_mutexes[philo->right_fork]);
	pthread_mutex_unlock(data->fork_mutexes[philo->left_fork]);
	philo->meals_had++;
}

void	state_fork(t_philo *philo, t_data *data)
{
	philo->state = FORK;
	print_philo_state_message(philo, data);
}
