/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:35:38 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/25 20:25:17 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static t_thread_args	*get_arguments_for_thread(t_philo *philo, t_data *data)
{
	t_thread_args	*args;

	args = malloc(sizeof(t_thread_args));
	if (args == NULL)
		return (print_error_message_and_return_null("malloc fail"));
	args->data = data;
	args->philo = philo;
	return (args);
}

static t_philo	*initialize_philo_info(int i, t_data *data, t_philo *philo)
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
		return (print_error_message_and_return_null("mutex init fail"));
	if (pthread_mutex_init(&philo->last_meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->state_mutex);
		return (print_error_message_and_return_null("mutex init fail"));
	}
	if (pthread_mutex_init(&philo->meals_had_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->state_mutex);
		pthread_mutex_destroy(&philo->last_meal_mutex);
		return (print_error_message_and_return_null("mutex init fail"));
	}
	return (philo);
}

t_philo	**initialize_philosopher_threads(t_data *data)
{
	t_philo			**philo;
	t_thread_args	*args;
	int				i;

	philo = malloc(data->philosophers_amount * sizeof(t_philo *));
	if (philo == NULL)
		return (print_error_message_and_return_null("malloc fail"));
	i = 0;
	data->initialized_threads = 0;
	data->initialization_failed = false;
	while (i < data->philosophers_amount)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (philo[i] == NULL)
		{
			data->initialization_failed = true;
			let_dinner_start(data);
			print_error_message("malloc fail");
			return (philo);
		}
		philo[i] = initialize_philo_info(i, data, philo[i]);
		if (philo == NULL)
		{
			data->initialization_failed = true;
			let_dinner_start(data);
			free (philo[i]);
			return (philo);
		}
		args = get_arguments_for_thread(philo[i], data);
		if (args == NULL)
		{
			data->initialization_failed = true;
			let_dinner_start(data);
			free (philo[i]);
			return (philo);
		}
		pthread_create(&(*philo[i]).thread, NULL, &dining_thread_main, args);
		data->initialized_threads++;
		i++;
	}
	return (philo);
}
