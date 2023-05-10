/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:32:58 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/10 14:05:45 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_if_philosophers_had_enough_meals(t_philo **philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philosophers_amount)
	{
		if (philos[i]->meals_had < data->meals_quota)
			return (false);
		i++;
	}
	return (true);
}

int	check_if_philosopher_starved(t_philo **philos, t_data *data)
{
	int	time_without_meal;
	int	i;

	i = 0;
	while (i < data->philosophers_amount)
	{
		time_without_meal = get_simulation_time(data) - philos[i]->last_meal_time;
		if (time_without_meal > data->time_to_starve)
			return (philos[i]->philo_id);
		i++;
	}
	return (0);
}

void	monitor(t_philo **philos, t_data *data)
{
	int	philo_that_starved;

	philo_that_starved = false;
	while (!philo_that_starved && !data->enough_meals)
	{
		philo_that_starved = check_if_philosopher_starved(philos, data);
		if (philo_that_starved)
			data->philo_starved = philo_that_starved;
		if (check_if_philosophers_had_enough_meals(philos, data) == true)
			data->enough_meals = true;
	}
}
