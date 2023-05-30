/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:35:38 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/30 17:26:34 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static t_thread_args	*get_arguments_for_thread(t_philo *philo, t_data *data)
{
	t_thread_args	*args;

	args = malloc(sizeof(t_thread_args));
	if (args == NULL)
		return (NULL);
	args->data = data;
	args->philo = philo;
	return (args);
}

static	t_philo	*initialize_philo_mutexes(t_philo *philo)
{
	if (pthread_mutex_init(&philo->state_mutex, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&philo->last_meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->state_mutex);
		return (NULL);
	}
	if (pthread_mutex_init(&philo->meals_had_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->state_mutex);
		pthread_mutex_destroy(&philo->last_meal_mutex);
		return (NULL);
	}
	return (philo);
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
	return (initialize_philo_mutexes(philo));
}

static t_philo	**handle_init_error(t_data *data,
	t_philo **philo, int i, char *error_message)
{
	print_error_message(error_message);
	data->initialization_failed = true;
	if (data->initialized_threads > 0)
		let_dinner_start(data);
	if (philo && philo[i])
		free (philo[i]);
	return (philo);
}

t_philo	**initialize_philosopher_threads(t_data *data)
{
	t_philo			**philo;
	t_thread_args	*args;
	int				i;

	data->initialized_threads = 0;
	data->initialization_failed = false;
	i = 0;
	philo = malloc(data->philosophers_amount * sizeof(t_philo *));
	if (philo == NULL)
		return (handle_init_error(data, philo, i, "malloc fail"));
	while (i < data->philosophers_amount)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (philo[i] == NULL)
			return (handle_init_error(data, philo, i, "malloc fail"));
		if (initialize_philo_info(i, data, philo[i]) == NULL)
			return (handle_init_error(data, philo, i, "mutex init fail"));
		args = get_arguments_for_thread(philo[i], data);
		if (args == NULL)
			return (handle_init_error(data, philo, i, "malloc fail"));
		pthread_create(&(*philo[i]).thread, NULL, &dining_thread_main, args);
		data->initialized_threads++;
		i++;
	}
	return (philo);
}
