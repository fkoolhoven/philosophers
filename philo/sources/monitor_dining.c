/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:32:58 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/19 13:34:19 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	check_if_philosophers_had_enough_meals(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	if (data->meals_quota_established == false)
		return (false);
	while (i < data->philosophers_amount)
	{
		if (philo[i]->meals_had < data->meals_quota)
			return (false);
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
		time_without_meal = get_simulation_time(data) - philo[i]->last_meal;
		if (time_without_meal > data->time_to_starve)
			return (philo[i]);
		i++;
	}
	return (NULL);
}

void	monitor_dining(t_philo **philos, t_data *data)
{
	t_philo	*philo_that_starved;

	while (!data->dinner_should_stop)
	{
		philo_that_starved = check_if_philosophers_starved(philos, data);
		if (philo_that_starved)
		{
			philo_that_starved->state = DIED;
			print_philo_state_message(philo_that_starved, data);
		}
		else if (check_if_philosophers_had_enough_meals(philos, data) == true)
		{
			data->dinner_should_stop = true;
			print_meals_quota_message(data);
		}
	}
}
