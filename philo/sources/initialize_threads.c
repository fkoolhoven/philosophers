/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:35:38 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/19 14:59:47 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	initialize_philo_information(int i, t_data *data, t_philo *philo)
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
	t_philo				**philo;
	t_thread_arguments	*args;
	int					i;

	philo = malloc(data->philosophers_amount * sizeof(t_philo *));
	if (philo == NULL)
		print_error_message_and_exit("malloc fail");
	i = 0;
	data->all_philosophers_present = false;
	while (i < data->philosophers_amount)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (philo[i] == NULL)
			print_error_message_and_exit("malloc fail");
		initialize_philo_information(i, data, philo[i]);
		args = malloc(sizeof(t_thread_arguments));
		if (args == NULL)
			print_error_message_and_exit("malloc fail");
		args->data = data;
		args->philo = philo[i];
		pthread_create(&(*philo[i]).thread, NULL, &dining_thread_start, args);
		i++;
	}
	data->start_time = get_current_time();
	data->all_philosophers_present = true;
	return (philo);
}
