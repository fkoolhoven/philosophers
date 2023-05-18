/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:21:17 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/18 16:19:50 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/colors.h"

void	meals_quota_message(t_data *data)
{
	char	*str;

	if (data->meals_quota != 1)
		str = "times";
	else
		str = "time";
	printf(CC_BOLD CC_GREEN"\nEvery philosopher has eaten at least "
		"%i %s!\n\n"CC_OFF, data->meals_quota, str);
}

int	get_philo_id(t_philo *philo, t_data *data)
{
	if (data->philo_starved)
		return (data->philo_starved);
	else
		return (philo->philo_id);
}

char	*get_philo_state(t_philo *philo, t_data *data)
{
	if (data->philo_starved)
		return (CC_RED"died"CC_OFF);
	else if (philo->state == FORK)
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

void	print_philo_state_message(t_philo *philo, t_data *data) // simplify this function?
{
	char	*state;
	int		philo_id;

	pthread_mutex_lock(&data->message_mutex);
	if (data->dinner_should_stop || data->enough_meals)
	{
		pthread_mutex_unlock(&data->message_mutex);
		return ;
	}
	philo_id = get_philo_id(philo, data);
	state = get_philo_state(philo, data);
	printf("%llu "CC_YELLOW"%i "CC_OFF""CC_BOLD"%s\n"CC_OFF,
		get_simulation_time(data), philo_id, state);
	if (data->philo_starved)
		data->dinner_should_stop = true;
	pthread_mutex_unlock(&data->message_mutex);
}
