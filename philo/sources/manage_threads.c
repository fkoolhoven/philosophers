/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:36:51 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/17 15:53:00 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	join_philosopher_threads(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->philosophers_amount)
	{
		pthread_join((*philo[i]).thread, NULL);
		i++;
	}
}

void	initialize_philo_information(int i, t_data *data, t_philo *philo)
{
	philo->philo_id = i + 1;
	philo->state = THINKING;
	philo->meals_had = 0;
	philo->last_meal = 0;
	philo->right_fork = philo->philo_id - 1;
	if (philo->philo_id != data->philosophers_amount)
		philo->left_fork = philo->philo_id;
	else
		philo->left_fork = 0;
}

t_philo	**initialize_philosopher_threads(t_data *data)
{
	int					i;
	t_philo				**philo;
	t_thread_arguments	*args;

	philo = malloc(data->philosophers_amount * sizeof(t_philo *));
	if (philo == NULL)
		error_message_exit("Malloc fail");
	i = 0;
	while (i < data->philosophers_amount)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (philo[i] == NULL)
			error_message_exit("Malloc fail");
		initialize_philo_information(i, data, philo[i]);
		args = malloc(sizeof(t_thread_arguments));
		if (args == NULL)
			error_message_exit("Malloc fail");
		args->data = data;
		args->philo = philo[i];
		pthread_create(&(*philo[i]).thread, NULL, &dining_thread_start, args);
		i++;
	}
	return (philo);
}
