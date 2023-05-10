/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:32:58 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/10 13:39:02 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_if_philosopher_starved(t_philo **philos, t_data *data)
{
	int	time_since_last_meal;
	int	i;

	i = 0;
	while (i < data->philosophers_amount)
	{
		time_since_last_meal = get_simulation_time(data) - philos[i]->last_meal_time;
		if (time_since_last_meal > data->time_to_starve)
			return (philos[i]->philo_id);
		i++;
	}
	return (0);
}

void	monitor(t_philo **philos, t_data *data)
{
	int	philo;

	philo = 0;
	while (true)
	{
		philo = check_if_philosopher_starved(philos, data);
		if (philo != 0)
		{
			data->philo_starved = philo;
			break ;
		}
		// if (check_if_philosophers_had_enough_meals() == true)
		// {
		// 	data->enough_meals = true;
		// }
	}
}
