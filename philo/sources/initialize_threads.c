/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:35:38 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/22 14:54:15 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static t_thread_args	*get_arguments_for_thread(t_philo *philo, t_data *data)
{
	t_thread_args	*args;

	args = malloc(sizeof(t_thread_args));
	if (args == NULL)
		print_error_message_and_exit("malloc fail");
	args->data = data;
	args->philo = philo;
	return (args);
}

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
	if (pthread_mutex_init(&philo->state_mutex, NULL) != 0)
		print_error_message_and_exit("mutex init fail");
	if (pthread_mutex_init(&philo->last_meal_mutex, NULL) != 0)
		print_error_message_and_exit("mutex init fail");
	if (pthread_mutex_init(&philo->meals_had_mutex, NULL) != 0)
		print_error_message_and_exit("mutex init fail");
}

t_philo	**initialize_philosopher_threads(t_data *data)
{
	t_philo			**philo;
	t_thread_args	*args;
	int				i;

	philo = malloc(data->philosophers_amount * sizeof(t_philo *));
	if (philo == NULL)
		print_error_message_and_exit("malloc fail");
	i = 0;
	while (i < data->philosophers_amount)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (philo[i] == NULL)
			print_error_message_and_exit("malloc fail");
		initialize_philo_information(i, data, philo[i]);
		args = get_arguments_for_thread(philo[i], data);
		pthread_create(&(*philo[i]).thread, NULL, &dining_thread_start, args);
		i++;
	}
	return (philo);
}
