/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_messages.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:21:17 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/25 16:56:57 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/colors.h"

void	print_meals_quota_message(t_data *data)
{
	char	*str;

	pthread_mutex_lock(&data->message_mutex);
	if (data->meals_quota != 1)
		str = "times";
	else
		str = "time";
	printf(CC_BOLD CC_GREEN"\nEvery philosopher has eaten at least "
		"%i %s!\n\n"CC_OFF, data->meals_quota, str);
	pthread_mutex_unlock(&data->message_mutex);
}

static char	*get_philo_state(t_philo *philo)
{
	if (philo->state == FORK)
		return (CC_CYAN"has taken a fork"CC_OFF);
	else if (philo->state == EATING)
		return (CC_GREEN"is eating"CC_OFF);
	else if (philo->state == SLEEPING)
		return (CC_MAGENTA"is sleeping"CC_OFF);
	else if (philo->state == THINKING)
		return (CC_BLUE"is thinking"CC_OFF);
	else if (philo->state == DIED)
		return (CC_RED"died"CC_OFF);
	return (NULL);
}

void	print_philo_state_message(t_philo *philo, t_data *data)
{
	char	*state;

	pthread_mutex_lock(&data->message_mutex);
	if (should_dinner_end(data))
	{
		pthread_mutex_unlock(&data->message_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->state_mutex);
	state = get_philo_state(philo);
	printf("%llu "CC_YELLOW"%i "CC_OFF""CC_BOLD"%s\n"CC_OFF,
		get_simulation_time(data), philo->philo_id, state);
	if (philo->state == DIED)
	{
		pthread_mutex_lock(&data->dinner_end_mutex);
		data->dinner_should_end = true;
		pthread_mutex_unlock(&data->dinner_end_mutex);
	}
	pthread_mutex_unlock(&philo->state_mutex);
	pthread_mutex_unlock(&data->message_mutex);
}
