/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:32:58 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/18 16:05:20 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_if_philosophers_had_enough_meals(t_philo **philos, t_data *data)
{
	int	i;

	i = 0;
	if (data->meals_quota_established == false)
		return (false);
	while (i < data->philosophers_amount)
	{
		if (philos[i]->meals_had < data->meals_quota)
			return (false);
		i++;
	}
	return (true);
}

int	check_if_philosophers_starved(t_philo **philos, t_data *data)
{
	int	time_without_meal;
	int	i;

	i = 0;
	while (i < data->philosophers_amount)
	{
		time_without_meal = get_simulation_time(data) - philos[i]->last_meal;
		if (time_without_meal > data->time_to_starve)
			return (philos[i]->philo_id);
		i++;
	}
	return (0);
}

void	monitor_dining(t_philo **philos, t_data *data)
{
	int	philo_starved;

	philo_starved = false;
	while (!philo_starved && !data->enough_meals)
	{
		philo_starved = check_if_philosophers_starved(philos, data);
		if (philo_starved)
			data->philo_starved = philo_starved;
		if (check_if_philosophers_had_enough_meals(philos, data) == true)
			data->enough_meals = true;
	}
}
