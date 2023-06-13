/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:32:58 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/06/13 14:32:33 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	check_if_meals_quota_is_met(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	if (data->meals_quota_established == false)
		return (false);
	while (i < data->philosophers_amount)
	{
		pthread_mutex_lock(&philo[i]->meals_had_mutex);
		if (philo[i]->meals_had < data->meals_quota)
		{
			pthread_mutex_unlock(&philo[i]->meals_had_mutex);
			return (false);
		}
		pthread_mutex_unlock(&philo[i]->meals_had_mutex);
		i++;
	}
	return (true);
}

static t_philo	*check_if_philosophers_starved(t_philo **philo, t_data *data)
{
	int	time_without_meal;
	int	i;

	i = 0;
	while (i < data->philosophers_amount)
	{
		pthread_mutex_lock(&philo[i]->last_meal_mutex);
		time_without_meal = get_simulation_time(data) - philo[i]->last_meal;
		pthread_mutex_unlock(&philo[i]->last_meal_mutex);
		if (time_without_meal > data->time_to_starve)
			return (philo[i]);
		i++;
	}
	return (NULL);
}

void	monitor_dining(t_philo **philos, t_data *data)
{
	t_philo	*philo_that_starved;

	while (!should_dinner_end(data))
	{
		philo_that_starved = check_if_philosophers_starved(philos, data);
		if (philo_that_starved)
		{
			pthread_mutex_lock(&philo_that_starved->state_mutex);
			philo_that_starved->state = DIED;
			pthread_mutex_unlock(&philo_that_starved->state_mutex);
			print_philo_state_message(philo_that_starved, data);
		}
		else if (check_if_meals_quota_is_met(philos, data) == true)
		{
			pthread_mutex_lock(&data->dinner_end_mutex);
			data->dinner_should_end = true;
			pthread_mutex_unlock(&data->dinner_end_mutex);
			print_meals_quota_message(data);
		}
	}
}
