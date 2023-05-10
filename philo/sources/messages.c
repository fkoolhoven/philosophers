/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:21:17 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/10 15:21:50 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/colors.h"

void	meals_quota_message(t_data *data)
{
	char	*string;

	pthread_mutex_lock(&data->message_mutex);
	if (data->meals_quota != 1)
		string = "times";
	else
		string = "time";
	printf(CC_BOLD CC_GREEN"\nEvery philosopher has eaten at least %i %s!\n\n"CC_OFF, data->meals_quota, string);
	exit(EXIT_SUCCESS);
	pthread_mutex_unlock(&data->message_mutex);
}


void	print_philo_state_message(t_philo *philo, t_data *data)
{
	char	*state;
	int		philo_id;

	pthread_mutex_lock(&data->message_mutex);
	state = NULL;
	philo_id = philo->philo_id;
	if (data->philo_starved)
	{
		state = CC_RED"died"CC_OFF;
		philo_id = data->philo_starved;
	}
	else if (philo->state == FORK)
		state = CC_CYAN"has taken a fork"CC_OFF;
	else if (philo->state == EATING)
		state = CC_GREEN"is eating"CC_OFF;
	else if (philo->state == SLEEPING)
		state = CC_MAGENTA"is sleeping"CC_OFF;
	else if (philo->state == THINKING)
		state = CC_BLUE"is thinking"CC_OFF;
	else if (philo->state == DIED)
		state = CC_RED"died"CC_OFF;
	if (!data->enough_meals)
	{
		printf("%llu "CC_YELLOW"%i "CC_OFF""CC_BOLD"%s\n"CC_OFF,
			get_simulation_time(data), philo_id, state);
		
	}
	if (state == CC_RED"died"CC_OFF)
		exit (EXIT_SUCCESS);
	pthread_mutex_unlock(&data->message_mutex);
}
