/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:36:51 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/08 16:37:17 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	join_philosopher_threads(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philosophers)
	{
		pthread_join((*philo[i]).thread, NULL);
		i++;
	}
}

t_philo	*initialize_philo_information(int i, t_data *data, t_philo *philo)
{
	philo->philo_nbr = i + 1;
	philo->data = data;
	philo->state = THINKING;
	philo->meals_had = 0;
	philo->last_meal_time = 0;
	philo->right_fork = philo->philo_nbr - 1;
	if (philo->philo_nbr != data->nbr_of_philosophers)
		philo->left_fork = philo->philo_nbr;
	else
		philo->left_fork = 0;
	return (philo);
}

t_philo	**create_philosopher_threads(t_data *data)
{
	int		i;
	t_philo	**philo;

	philo = malloc(data->nbr_of_philosophers * sizeof(t_philo *));
	if (philo == NULL)
		error_message_exit("Malloc fail");
	i = 0;
	while (i < data->nbr_of_philosophers)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (philo[i] == NULL)
			error_message_exit("Malloc fail");
		philo[i] = initialize_philo_information(i, data, philo[i]);
		pthread_create(&(*philo[i]).thread, NULL, &dining, philo[i]);
		i++;
	}
	return (philo);
}
